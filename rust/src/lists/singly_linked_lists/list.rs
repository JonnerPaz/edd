use crate::lists::node::Node;
use std::{fmt::Debug, ops::Deref};

#[derive(Debug)]
pub struct List<T> {
    head: Option<Box<Node<T>>>,
    length: u32,
}

impl<T> List<T> {
    pub fn new() -> List<T> {
        List {
            head: None,
            length: 0,
        }
    }

    pub fn push(&mut self, data: T) -> &Self
    {
        let my_box = Box::new(8);
        let my_def_box = my_box.downcast::<String>();
        let new_node = Box::new(Node::new(data));

        if self.head.is_none() && self.tail.is_none() {
            self.head = Some(new_node);
            unsafe {
                self.tail = Some(&mut *new_node);
            }
            self.length += 1;

            return self;
        } else {
            self.tail.as_mut().unwrap().(*next) = Some(new_node);
        }

        // is mutable because we are going to replace it, eventually
        let mut current_link = &mut self.head;

        // find the last node
        while let Some(node) = current_link {
            current_link = &mut node.next;
        }

        // current_link now points to last node, which is None
        // now we can replace it
        current_link.replace(new_node);
        self.length += 1;

        self
    }

    pub fn pop(&mut self, data: T) -> Option<T> {
        if self.length <= 0 {
            return None;
        }

        let current_link = &mut self.head;

        self.head.take().map(|node| node.data)
    }
}
