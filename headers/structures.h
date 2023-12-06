
#include <iostream>
#include "useful_functions.h"





namespace data_structures {

	namespace {


		template <typename data_> class node_root {

			protected:
				data_ this_data;
			
			public:

				node_root(){}

				node_root(data_ new_data) : this_data(new_data){
				}

				void set_data(data_ d) {
					this->this_data = d;
				}

				data_ get_data() const {
					return this->this_data;
				}

				data_ &get_data_ref() {
					return this->this_data;
				}

		};


		template <typename data_, typename indx_ = signed long> class numbered_node : public node_root<data_> {


			private:
				indx_ index;



			protected:

				void set_index(indx_ index) {
					this->index = index;
				}


				indx_ get_index() const {
					return this->index;
				}

			public:

				numbered_node() {
				}

				numbered_node(data_ new_data, indx_ index = -1) : node_root<data_>(new_data) {
					this->index = index;
				}

		};


		template <typename data_> class linear_node : public node_root<data_> {
			
			protected:
				linear_node<data_>* next_node;
				linear_node<data_>* previous_node;

			public:

				linear_node() {
					this->next_node = nullptr;
				}

				linear_node(data_ new_data, linear_node<data_>* next = nullptr, linear_node<data_>* previous = nullptr) {
					this->this_data = new_data;
					this->next_node = next;
					this->previous_node = previous;
				}

				void set_next(linear_node<data_>* next) {
					this->next_node = next;
				}

				linear_node<data_>* get_next() const {
					return this->next_node;
				}

				void set_previous(linear_node<data_>* previous) {
					this->previous_node = previous;
				}

				linear_node<data_>* get_previous() const {
					return this->previous_node;
				}

		};


		template <typename data_> class bst_node : public node_root<data_> {

			private:
				bst_node<data_> *left_child, *right_child;

			public:

				bst_node() {
					this->left_child = this->right_child = nullptr;
					this->set_index(-1);
				}

				bst_node(data_ new_data) {
					this->this_data = new_data;
					this->left_child = this->right_child = nullptr;
				}

				void set_left_child(bst_node<data_>* left) {
					this->left_child = left;
				}

				void set_right_child(bst_node<data_>* right) {
					this->right_child = right;
				}

				bst_node<data_>* get_left_child() {
					return this->left_child;
				}

				bst_node<data_>* get_right_child() {
					return this->right_child;
				}

		};

	}


	template <typename data_> class linear_linked_list {


		private:
			linear_node<data_> *front, *rear, *frame;
			unsigned long size, frame_index;

			void node_shifter(linear_node<data_>* this_node, unsigned long node_index, signed long by) {

				signed long start_index = (signed long) node_index;
				while ((by != 0) && (this_node != nullptr) && (node_index != by)) {
					if (by > 0) {
						this_node = this_node->get_next();
						node_index = node_index + 1;
					}
					else {
						this_node = this_node->get_previous();
						node_index = node_index - 1;
					}
				}
			}

			void frame_shifter(signed long by) {
				while ((by != 0) && (this->frame != nullptr)) {
					this->frame = (by > 0) ? this->frame->get_next() : this->frame->get_previous();
					this->frame_index = (by > 0) ? this->frame_index + 1 : this->frame_index - 1;
					by = (by > 0) ? by - 1 : by + 1;
				}
			}


		public:

			linear_linked_list() {
				this->front = this->rear = this->frame = nullptr;
				this->size = 0;
			}


			linear_linked_list(data_ new_data) {
				this->front = this->rear = this->frame = new linear_node<data_>(new_data);
				this->size = 1;
			}


			// Copy Constructor

			linear_linked_list(linear_linked_list<data_>& other_list) {
				if (this == &other_list) {
					return;
				}
				this->size = 0;
				unsigned long index;
				for (index = 0; index < other_list.length(); index = index + 1) {
					this->push(other_list.peek(index));
				}
			}


			~linear_linked_list() {
				this->reset();
			}

			// Operator Overloading.

			// Assignment Operators
			// TODO CREATE ASSIGNMENT OPERATORS

			// Comparison operators

			bool operator==(linear_linked_list<data_>& other) {
				// fprintf(stderr, "== operator not yet implemented\n");
				exit(EXIT_FAILURE);
				if (this == *other) {
					return true;
				}
				unsigned long other_index = 0;

				for (this->frame = this->front, this->frame_index = 0; this->frame != nullptr; this->frame = this->frame->get_next(), this->frame_index = this->frame_index + 1) {
					if (this->frame->get_data() != other[this->frame_index]) {
						return false;
					}
				}
				return true;
			}




			bool operator!=(linear_linked_list<data_>& other) {
				// fprintf(stderr, "!= operator not yet implemented\n");
				exit(EXIT_FAILURE);
				if (this != *other) {
					return true;
				}
				unsigned long other_index = 0;

				for (this->frame = this->front, this->frame_index = 0; this->frame != nullptr; this->frame = this->frame->get_next(), this->frame_index = this->frame_index + 1) {
					if (this->frame->get_data() == other[this->frame_index]) {
						return false;
					}
				}
				return true;
			}




			bool operator<=(linear_linked_list<data_>& other) {
				// fprintf(stderr, "<= operator not yet implemented\n");
				exit(EXIT_FAILURE);
			}



			bool operator>=(linear_linked_list<data_>& other) {
				// fprintf(stderr, "=> operator not yet implemented\n");
				exit(EXIT_FAILURE);
			}




			data_& operator [](signed long index) {
				try {
					this->peek(index);
					return this->frame->get_data_ref();
				}
				catch (std::range_error except) {
					throw except;
				}
			}





			/**
			 * @brief Check if the current linked list is empty or not.
			 * 
			 * @returns `(bool)` : true if the linked list is empty, false otherwise.
			*/
			bool empty() const {
				return (this->size == 0);
			}





			/**
			 * @brief Get the size of the linked list.
			 * 
			 * @returns `(unsigned long)` : The length of the linked list.
			*/
			unsigned long length() const {
				return this->size;
			}





			/**
			 * @brief Empties out the linked list and frees up memory.
			 * 
			 * @returns void.
			*/
			void reset() {
				// // std::cout << "Inside reset method" << // std::endl;
				this->frame = this->front;
				while (this->frame != nullptr) {
					this->front = this->frame->get_next();
					delete this->frame;
					this->frame = this->front;
				}
				this->size = 0;
			}





			/**
			 * @brief Push new data onto the linked list.
			 * 
			 * @note Can push to negative indexes. Negative indexes will push from the back of the list.
			 * 
			 * @param new_data `(Generic)` : The new data to be pushed onto the linked list.
			 * 
			 * @param index `(signed long)` : The index where the data should be pushed to. Defaults to -1.
			 * 
			 * @returns void.
			 * 
			 * @throws Throws a `std::range_error` if the index passed in references an index greater than the current size.
			 * 
			*/
			void push(data_ new_data, signed long index = -1) {
				unsigned long add_index = (index < 0) ? (this->size - (unsigned long) useful_functions::absolute<signed long>(index)) + 1 : (unsigned long) useful_functions::absolute<signed long>(index);
				if (add_index > this->size) {
					throw std::range_error("Cannot push data to negative index whose absolute value converts to a larger value than the size of the list");
				}
				
				linear_node<data_>* new_node = new linear_node<data_>(new_data);
				
				if (this->size == 0) {
					this->front = this->rear = this->frame = new_node;
				}

				else if (this->size == 1) {

					if (add_index == 0) {
						this->front->set_previous(new_node);
						this->front->get_previous()->set_next(this->front);
						this->front = this->front->get_previous();
						this->frame = this->front;
					}

					else {
						// index is 1
						this->rear->set_next(new_node);
						this->rear->get_next()->set_previous(this->rear);
						this->rear = this->rear->get_next();
						this->frame = this->rear;
					}
				}

				else {
					if (add_index == 0) {
						this->front->set_previous(new_node);
						this->front->get_previous()->set_next(this->front);
						this->front = this->front->get_previous();
						this->frame = this->front;
					}
					else if (add_index == this->size) {
						this->rear->set_next(new_node);
						this->rear->get_next()->set_previous(this->rear);
						this->rear = this->rear->get_next();
						this->frame = this->rear;
					}
					else {
						// this is where some extra work comes into play.
						signed long from_first = (signed long) add_index, from_rear = (signed long) (this->size - add_index), from_frame = (signed long) add_index - (signed long) add_index;
						unsigned long frame_abs = (from_frame < 0) ? ((unsigned long) (-1 * from_frame)) : (unsigned long) from_frame;
						signed long* signed_lists[] = {&from_first, &from_rear, &from_frame};
						useful_functions::selection_sort<signed long>(signed_lists, 3, true);
						
						if (signed_lists[0] == &from_first) {
							// shortest distance is from the front
							this->frame = this->front;
							this->frame_index = 0;
							this->frame_shifter(from_first);
						}
						else if (signed_lists[0] == &from_rear) {
							// shoftest distance is from the rear
							this->frame = this->rear;
							this->frame_index = this->size - 1;
							this->frame_shifter((signed long) ( -1 * from_rear));
						}
						else {
							// shortest distance is from the frame
							// fprintf(stdout, "Inside else branch of the push method. Pushing data towards the center of the list\n");
							this->frame_shifter(from_frame);
						}

						// Now frame should be at the proper index.
						new_node->set_previous(this->frame->get_previous());
						this->frame->get_previous()->set_next(new_node);
						this->frame->set_previous(new_node);
						new_node->set_next(this->frame);
						this->frame = this->frame->get_previous();

					}
				}
				this->size = this->size + 1;
			}





			/**
			 * @brief Peek at the data inside the linked list at a specific index.
			 * 
			 * @param index `(Generic)` : Defaults to -1. The index whose data is to be looked up.
			 * 
			 * @note This method can accept negative indexes. If the index references data 
			 * outside the range of the linked list, a length error is thrown.
			 * 
			 * @returns `(Generic)` : The data at the index specified.
			*/
			data_ peek(signed long index = -1) {
				unsigned long peek_index = (index < 0) ? (this->size - ((unsigned long) index) - 1) : (unsigned long) index;
				if (this->size == 0) {
					throw std::length_error("linear linked list is empty.");
				}
				if (peek_index == 0) {
					this->frame = this->front;
					this->frame_index = 0;
				}
				else if (peek_index == this->size - 1) {
					this->frame = this->rear;
					this->frame_index = this->size - 1;
				}
				else {
					// This is where some extra work comes into play.
					// this is constly on a smaller linked list,
					// but the payoff is big for a larger linked list.
					unsigned long from_first = peek_index, from_rear = this->size - 1 - peek_index, from_frame = ((signed long) peek_index - (signed long) this->frame_index);
					unsigned long* distances[] = {&from_first, &from_rear, &from_frame};
					useful_functions::insertion_sort<unsigned long>(distances, 3, true);
					if (distances[0] == &from_first) {
						this->frame = this->front;
						this->frame_index = 0;
						this->frame_shifter((signed long) from_first);
					}
					else if (distances[0] == &from_rear) {
						this->frame = this->rear;
						this->frame_index = this->size - 1;
						this->frame_shifter((signed long) from_rear);
					}
					else {
						// frame is the shortest distance to traverse
						this->frame_shifter((index < 0) ? ((signed long) from_frame * -1) : ((signed long) from_frame));
					}
				}
				// fprintf(stdout, "\tAbout to return %lu at index %lu\n", this->frame->get_data(), this->frame_index);
				return this->frame->get_data();
			}


	};


	template <typename data_> class binary_search_tree {

		private:
			unsigned long size;
			signed long height;
			bst_node<data_>* root;
		

			void push_new_data(bst_node<data_>* current, data_ new_data, signed long current_height) {
				// fprintf(stdout, "Inside the push_new_data\n");
				if (current == nullptr) {
					return;
				}
				else if (new_data >= current->get_data()) {
					// go to the right of the current node.
					if (current->get_right_child() == nullptr) {
						// set the child here.
						current->set_right_child(new bst_node<data_>(new_data));
						this->size = this->size + 1;
						if (current_height + 1 > this->height) {
							this->height = this->height + 1;
						}
						return;
					}
					this->push_new_data(current->get_right_child(), new_data, current_height + 1);
				}
				else {
					// go to the left of the current node.
					if (current->get_left_child() == nullptr) {
						// set the child here
						current->set_left_child(new bst_node<data_>(new_data));
						this->size = this->size + 1;
						if (current_height + 1 > this->height) {
							this->height = this->height + 1;
						}
						return;
					}
					this->push_new_data(current->get_left_child(), new_data, current_height + 1);
				}
			}

			void update_heights(bst_node<data_>* current, signed long this_height) {
				if (current == nullptr) {
					return;
				}
				current->set_height(this_height);
				update_heights(current->get_left_child(), this_height + 1);
				update_heights(current->get_right_child(), this_height + 1);
				return;
			}

			signed long height_of(bst_node<data_>* current, data_ data, signed long current_height = -1) {
				if (current == nullptr) {
					return -1;
				}
				if (current->get_data() == data) {
					return current_height;
				}
				return this->height_of((data > current->get_data()) ? current->get_right_child() : current->get_left_child(), data, current_height + 1);
			}

			void free_tree(bst_node<data_>* current) {
				if (current == nullptr) {
					return;
				}

				free_tree(current->get_left_child());
				free_tree(current->get_right_child());
				delete current;
			}

			signed long get_subtree_height(bst_node<data_>* current) {
				if (!current) {
					return -1;
				}
				signed long left_child = this->get_subtree_height(current->get_left_child());
				signed long right_child = this->get_subtree_height(current->get_right_child());
				return 1 + useful_functions::max_data<signed long>(left_child, right_child);
			}

			void update_tree_height() {
				this->height = useful_functions::max_data<signed long>(this->get_subtree_height(this->root->get_left_child()), this->get_subtree_height(this->root->get_right_child()));
			}

			bst_node<data_>* get_most_child(bst_node<data_>* current, bool left = true) {
				if (current == nullptr) {
					return nullptr;
				}
				if (left) {
					if (current->get_left_child() == nullptr) {
						return current;
					}
					return this->get_most_child(current->get_left_child(), true);
				}
				else {
					if (current->get_right_child() == nullptr) {
						return current;
					}
					return this->get_most_child(current->get_right_child(), false);
				}
			}

			void find_and_remove(bst_node<data_>* current, data_ remove_me) {
				if (current == nullptr) {
					return;
				}
				if (current->get_data() == remove_me) {
					/* 
						The current node is the node that is being deleted 
					*/


					// holds the leftmost or rightmost leaf child.
					bst_node<data_>* leaf_child;

					// the current node has a left and right child
					if (current->get_left_child() && current->get_right_child()) {
						
						// leaf_child is the left most child of the current node's right child.
						leaf_child = this->get_most_child(current->get_right_child());
						// fprintf(stdout, "For current leaf_child with both children, %s child has data\n", leaf_child->get_left_child() ? "Left" : (leaf_child->get_right_child()) ? "Right" : "No");
						current->set_data(leaf_child->get_data());
						delete leaf_child;
					}

					// there is a left child, but no right child.
					else if (current->get_left_child() && !current->get_right_child()) {
						
						// leaf_child is the right most child of the current node's left child.
						leaf_child = this->get_most_child(current->get_left_child(), false);
						// fprintf(stdout, "For current leaf_child with left child only, %s child has data\n", leaf_child->get_left_child() ? "Left" : (leaf_child->get_right_child()) ? "Right" : "No");
						current->set_data(leaf_child->get_data());
						delete leaf_child;
					}

					// there is a right child, but no left child.
					else {

						// leaf_child is the left most child of the current node's right child
						leaf_child = this->get_most_child(current->get_right_child());
						// fprintf(stdout, "For current leaf_child with right child only, %s child has data\n", leaf_child->get_left_child() ? "Left" : (leaf_child->get_right_child()) ? "Right" : "No");
						current->set_data(leaf_child->get_data());
						delete leaf_child;
					}
					this->update_tree_height();
					this->size = this->size - 1;
				}
				this->find_and_remove((remove_me > current->get_data()) ? current->get_right_child() : current->get_left_child(), remove_me);
			}


		public:

			binary_search_tree() {
				this->size = 0;
				this->height = -1;
				this->root = nullptr;
			}

			binary_search_tree(data_ new_data) {
				this->root = new bst_node<data_>(new_data);
				this->root->set_height(0);
				this->size = 1;
				this->height = 0;
			}

			~binary_search_tree() {
				this->free_tree(this->root);
			}

			unsigned long get_height() const {
				return this->height;
			}

			signed long get_size() const {
				return this->size;
			}

			bool empty() const {
				return this->size == 0;
			}

			void add(data_ new_data) {
				if (this->size == 0) {
					this->root = new bst_node<data_>(new_data);
					this->size = 1;
					this->height = 0;
				}
				else {
					this->push_new_data(this->root, new_data, 0);
				}
			}

			bool contains(data_ to_find) {
				if (this->size == 0) {
					return false;
				}
				return this->height_of(this->root, to_find, 0) != -1;
			}

			signed long data_height(data_ to_find) {
				if (this->size == 0) {
					return -1;
				}
				return this->height_of(this->root, to_find, 0);
			}

			void reset() {
				this->free_tree(this->root);
			}

			void remove(data_ to_remove) {
				if (this->size > 0) {
					if (this->size == 1) {
						this->free_tree(this->root);
						this->size = 0;
						this->height = -1;
					}
					else {
						// fprintf(stdout, "Removing %lu\n", to_remove);
						this->find_and_remove(this->root, to_remove);
					}
				}
			}


	};


}