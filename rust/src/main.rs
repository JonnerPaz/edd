use rust::lists::node::Node;
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

fn insert_node_from_beginning<T>(head: &mut Option<Box<Node<T>>>, data: T)
where
    T: Debug + PartialOrd,
{
    let mut new_node = Box::new(Node::new(data));

    if let Some(current_node) = head.as_ref() {
        if new_node.data < current_node.data {
            // .takes gives Box<Node<T>> ownership inside head
            // to new_node. new_node now owns what's inside head
            new_node.set_next_node(head.take());
        }

        // head now points to new_node
        *head = Some(new_node);
    } else {
        *head = Some(new_node);
    }
}

fn insert_node_from_end<T>(head: &mut Option<Box<Node<T>>>, data: T)
where
    T: Debug + PartialOrd,
{
    let new_node = Box::new(Node::new(data));
    // current_link points to last node
    let mut current_link = head;

    while let Some(node) = current_link {
        // current_link is gonna point to next node until it points to None
        current_link = &mut node.next;
    }

    // once current_link points to None,
    // we will point it to new_node
    *current_link = Some(new_node);
}

fn insert_nodes_in_between<T>(head: &mut Option<Box<Node<T>>>, data: T)
where
    T: Debug + PartialOrd,
{
    let mut new_node = Box::new(Node::new(data));
    let mut current_link = head;

    loop {
        let should_insert = match current_link {
            Some(node) => new_node.data <= node.data,
            None => true, // Reached the end, insert
        };

        if should_insert {
            break;
        }

        // current_link is gonna point to next node until it points to real node to insert
        current_link = &mut current_link.as_mut().unwrap().next;
    }

    new_node.set_next_node(current_link.take());
    *current_link = Some(new_node);
}

fn delete_node<T>(head: &mut Option<Box<Node<T>>>, data: T)
where
    T: Debug + PartialOrd,
{
    let mut current_link = head;

    // iterates until current_link points to node to delete
    // or until current_link points to None
    loop {
        let should_delete = match current_link {
            Some(node) => node.data == data,
            None => false,
        };

        if should_delete {
            break;
        } else if current_link.is_none() {
            return;
        }

        current_link = &mut current_link.as_mut().unwrap().next;
    }

    match current_link {
        Some(node) => {
            *current_link = node.next.take();
        }
        None => {}
    }
}

fn main() {
    // Initial nodes
    let mut first_node = Box::new(Node::new(0));
    let second_node = Box::new(Node::new(1));
    // insert second_node into first_node
    first_node.set_next_node(Some(second_node)); // now second_node from here is dead

    // Real list
    let mut list = Some(first_node);
    traversing_list(&list); // 0, 1

    println!("Inserting nodes from beginning");
    insert_node_from_beginning(&mut list, -1);
    traversing_list(&list); // -1, 0, 1

    println!("Inserting nodes from end");
    insert_node_from_end(&mut list, 3);
    traversing_list(&list); // -1, 0, 1, 3

    println!("Inserting nodes from end");
    insert_nodes_in_between(&mut list, 2);
    traversing_list(&list); // -1, 0, 1, 2, 3

    println!("Deleting node");
    delete_node(&mut list, -1);
    traversing_list(&list); // 0, 1, 2, 3

    delete_node(&mut list, 3);
    traversing_list(&list); // 0, 1, 2

    delete_node(&mut list, 1);
    traversing_list(&list); // 0, 2
} // in rust, after main func, list goes out of scope so it becomes None
