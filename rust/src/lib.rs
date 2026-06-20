#[derive(Debug)]
pub struct Node<T> {
    pub data: T,
    pub next: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    pub fn new(data: T) -> Node<T> {
        Node { data, next: None }
    }

    pub fn get_next_node(&self) -> Option<&Box<Node<T>>> {
        self.next.as_ref()
    }

    pub fn set_next_node(&mut self, next: Option<Box<Node<T>>>) -> () {
        self.next = next;
    }
}
