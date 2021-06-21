//
// Created by Robin on 2021-05-27.
//
#pragma once
#include <cstdint>
#include "allocator.h"
#include "tools/ptr.h"
namespace Impact {
    template<typename C>
    class Spatial_octree {
    public:
        Spatial_octree() {
            this->root = (uint16_t)p_nodes.template alloc<Impact::vec3,Impact::vec3>({0,0,0},{std::numeric_limits<scalar>::max(),std::numeric_limits<scalar>::max(),std::numeric_limits<scalar>::max()});
        }
        C* at(uint16_t index) {
            return &this->p_data.at(index)->item;
        }
        template<typename... Args>
        uint16_t insert(const vec3& position, const vec3& half_axis, Args&&... args) {
            auto data = (uint16_t)p_data.alloc(std::forward<Args>(args)...);
            auto leaf = (uint16_t)p_nodes.alloc(data,position,half_axis);
            p_data.at(data)->leaf = leaf;
            p_nodes[this->root].insert(p_nodes,leaf);
            return data;
        }

        void remove(uint16_t data_node) {
            auto* c = p_data.at(data_node);
            p_nodes.at(this->root).remove(c->leaf);
            p_nodes.delete_entry(c->leaf);
            p_data.delete_entry(data_node);
        }
        void move(uint16_t data_node, const vec3& position) {
            auto& c = p_data.at(data_node);

            p_nodes.at(this->root).remove(c.leaf);
            Node& n = p_nodes.at(c.leaf);
            n.box.position = position;
        }
        void move(uint16_t data_node, const vec3& position, const vec3& half_axis) {
            auto& c = p_data.at(data_node);
            p_nodes.at(this->root).remove(c.leaf);
            Node& n = p_nodes.at(c.leaf);
            n.box.half_axis = half_axis;
            n.box.position = position;
            p_nodes[this->root].insert(p_nodes,c.leaf);
        }
        void intersect(uint16_t target_node, std::vector<C&> target) {
            auto& obj = p_data.at(target_node);
            Node& leaf = p_nodes.at(obj.leaf);
            leaf.search_flag = true; /// Avoid searching for the target node.
            Node& root = p_nodes.at(this->root);
            std::vector<Node&> nodes;
            root.intersect(nodes,p_nodes,leaf.box);
            leaf.search_flag = false;
            for (Node& n : nodes) {
                target.template emplace_back(p_data.at(n.data));
                n.search_flag = false;
            }
        }
        void intersect(const vec3& position, const vec3& half_radius, std::vector<C*>& target,std::initializer_list<uint16_t> exclusions = {}) {
            for (auto& i : exclusions) {
                auto* obj = p_data.at(i);
                p_nodes.at(obj->leaf)->search_flag = true;
            }

            Boundingbox b(position, half_radius);
            Node* root = p_nodes.at(this->root);
            std::vector<Node*> nodes;
            root->intersect(nodes,p_nodes,b);
            for (auto* n : nodes) {

                target.emplace_back(&p_data.at(n->data)->item);
                n->search_flag = false;
            }
            for (auto& i : exclusions) {
                auto* obj = p_data.at(i);
                p_nodes.at(obj->leaf)->search_flag = true;
            }
        }
        /**
         * Find all unique intersections in the octree.
         * @param target
         */
        void intersect(std::vector<std::pair<C*,C*>>& target) {
            Pool_array<1,uint8_t,bool> flags;
            std::vector<std::pair<uint16_t,uint16_t>> temp_target;
            this->p_nodes.at(this->root)->intersect(temp_target,this->p_nodes,flags);
            target.clear();
            target.reserve(temp_target.size());
            for (auto& pair: temp_target) {
                auto* first = this->at(this->p_nodes[pair.first].data);
                auto* second = this->at(this->p_nodes[pair.second].data);
                target.emplace_back(first, second);
                //target.emplace_back(this->p_data.at(pair.first), this->p_data.at(pair.second));
            }
        }
        C& get(uint16_t pointer) {
            return this->p_data.at(pointer)->item;
        }
        const C& get(uint16_t pointer) const{
            return this->p_data.at(pointer)->item;
        }
    private:
        template<typename T>
        struct Container{
            T item;
            uint16_t leaf = 0;
            template<typename... Args>
            Container(Args&&... args) : item(std::forward<Args>(args)...){}
        };
        struct Node {
        public:
            void insert(Same_arena_allocator<1,uint8_t,Node>& nodes, uint16_t leaf) {
                if (!has_subtree) {
                    if (size == 8) {
                        this->split(nodes);
                    } else {
                        this->children[size++] = leaf;
                        return;
                    }
                }
                for (uint8_t i = 0; i < 8;++i) {
                    if (nodes.at(leaf)->box.aabb_intersect(nodes.at(this->children[i])->box)) {
                        nodes[children[i]].insert(nodes,leaf);
                    }
                }
            }
            uint8_t remove(Same_arena_allocator<1,uint8_t,Node>& nodes, uint16_t target_node) {
                if(this->has_subtree) {
                    uint8_t size = 0;
                    for (uint8_t i = 0; i < 8; ++i) {
                        auto new_size = nodes.at(this->children[i])->remove(nodes,target_node);
                        if (new_size > size) size = new_size;
                    }

                    if (size == 0) {
                        for (uint8_t i = 0; i < 8; ++i) {
                            nodes.delete_entry(this->children[i]);
                        }
                        this->size = 0;
                        this->has_subtree = false;
                    }

                    return size;
                } else {
                    for (uint8_t i = 0; i < this->size; ++i) {
                        if (target_node == this->children[i]) {
                            //nodes->free(this->children[i]);
                            this->size--;
                            if (i < this->size) {
                                this->children[i] = this->children[this->size];
                            }
                            break;
                        }
                    }
                }
            }
            void intersect(std::vector<Node*>& target,Same_arena_allocator<1,uint8_t,Node>& nodes, const Boundingbox& area) {
                if (this->has_subtree) {
                    for (uint8_t i = 0; i < this->size; ++i) {
                        Node* n = nodes.at(this->children[i]);
                        if (n->box.aabb_intersect(area)) {
                            n->intersect(target,nodes,area);
                        }
                    }
                } else {
                    for (uint8_t i = 0; i < this->size; ++i) {
                        Node* n = nodes.at(this->children[i]);
                        if (!n->search_flag && n->box.aabb_intersect(area)) {
                            target.emplace_back(n);
                            n->search_flag = true;
                        }
                    }
                }
            }

            void intersect(std::vector<std::pair<uint16_t,uint16_t>>& target, Same_arena_allocator<1,uint8_t,Node>& nodes, Pool_array<1,uint8_t,bool>& flags) {
                if(this->has_subtree) {
                    for (uint8_t i = 0; i < this->size; ++i) {
                        nodes.at(this->children[i])->intersect(target,nodes,flags);
                    }
                } else {
                    if (this->size >= 2) {
                        for (uint8_t i = 0; i < this->size-1; ++i) {
                            for (uint8_t k = i+1; k < this->size; ++k) {

                                auto largest = this->children[i];
                                auto smallest = this->children[k];
                                if (this->children[k] > largest) {
                                    largest = this->children[k];
                                    smallest = this->children[i];
                                }
                                Node* n1 = nodes.at(largest);
                                Node* n2 = nodes.at(smallest);
                                uint32_t index = (largest*largest+largest)*0.5;
                                if (flags.has_page_indexed(index)) {
                                    if (!flags[index+smallest]) {
                                        if (n1->box.aabb_intersect(n2->box)) {
                                            target.emplace_back(largest,smallest);
                                            flags[index+smallest] = true;
                                        }
                                    }
                                } else {
                                    if (n1->box.aabb_intersect(n2->box)) {
                                        target.emplace_back(largest,smallest);
                                        flags.push(index+smallest,true);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Node(uint16_t data,const vec3& position, const vec3& half_axis) : leaf(true),box(position,half_axis,true){this->data = data;this->search_flag = false;}
            Node(const vec3& position, const vec3& half_axis) : leaf(false), box(position,half_axis,true){this->size = 0;}
            Node() {}


            void split(Same_arena_allocator<1,uint8_t,Node>& nodes) {
                uint16_t temp_children[8];
                std::copy(this->children,this->children+8,temp_children);
                auto half_axis = this->box.half_axis*0.5f;
                uint8_t i = 0;
                for (int8_t x = -1; x <= 1; x += 2) {
                    for (int8_t y= -1; y <= 1; y += 2) {
                        for (int8_t z = -1; z <= 1; z += 2) {
                            this->children[i] = (uint16_t)nodes.alloc(vec3(this->box.position.x*0.5f+half_axis.x*x,this->box.position.y*0.5f+half_axis.y*y,this->box.position.z*0.5f+half_axis.z*z),half_axis);
                            i++;
                        }
                    }
                }
                this->has_subtree = true;
                for (uint8_t i = 0; i<8;++i) {
                    this->insert(nodes,temp_children[i]);
                }
            }

            union {
                struct {
                    uint16_t children[8];
                    uint8_t size;
                };
                struct {
                    ptr_primitive data;
                    bool search_flag;
                };

            };
            Boundingbox box;
            bool has_subtree = false;
            bool leaf;
        };


        Same_arena_allocator<1,uint8_t,Node> p_nodes;
        Same_arena_allocator<1,uint8_t,Container<C>> p_data;
        uint16_t root = 0;
        bool search_flag = false;
    };
}