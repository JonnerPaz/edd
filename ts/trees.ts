class BinaryNode<T> {
  value: T;
  left: BinaryNode<T> | null;
  right: BinaryNode<T> | null;

  constructor(value: T) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

class BinarySearchTree<T> {
  root: BinaryNode<T> | null;

  constructor() {
    this.root = null;
  }

  public insert(value: T): void {
    const newNode = new BinaryNode(value);

    if (!this.root) {
      this.root = newNode;
      return;
    }

    let curNode = this.root;
    while (true) {
      if (value < curNode.value) {
        // insert if left is null, else go left
        if (!curNode.left) {
          curNode.left = newNode;
          break;
        }
        curNode = curNode.left;
      } else {
        // insert if right is null, else go right
        if (!curNode.right) {
          curNode.right = newNode;
          break;
        }
        curNode = curNode.right;
      }
    }
  }
}

const bst = new BinarySearchTree<number>();
bst.insert(9);
bst.insert(4);
bst.insert(6);
bst.insert(20);
bst.insert(170);
bst.insert(15);
bst.insert(1);
