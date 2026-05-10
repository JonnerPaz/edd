use rust::Node;
use std::fmt::Debug;

fn traversing_list<T>(head: &Option<Box<Node<T>>>)
where
    T: Debug,
{
    let mut current = head.as_ref();

    while let Some(node) = current {
        print!("{:?},", node.data);

        // current now points to next node
        current = node.get_next_node();

        if current.is_none() {
            println!("\n");
            break;
        }
    }
}

fn main() {
    // primer nodo
    let mut head = Box::new(Node::new(0));
    let second_node = Box::new(Node::new(1));
    head.set_next_node(Some(second_node)); // now second_node from here is dead

    traversing_list(&Some(head)); // 0, 1

    println!("Inserting nodes from beginning")
}
