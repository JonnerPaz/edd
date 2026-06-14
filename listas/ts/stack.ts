import { CustomNode } from "./nodes.js";

export class Stack<T> {
  private first: CustomNode<T> | null = null;
  private last: CustomNode<T> | null = null;
  protected size = 0;

  constructor(firstNode?: T) {
    if (firstNode) {
      this.push(firstNode);
    } else {
      this.first = null;
    }
  }

  push(value: T): number {
    const node = new CustomNode(value);

    if (!this.first) {
      this.first = node;
      this.last = node;
    } else {
      node.next = this.first;
      this.first = node;
    }

    return ++this.size;
  }

  pop(): T | null {
    if (!this.first) return null;
    const value = this.first.value;
    if (this.first === this.last) {
      this.last = null;
    }
    this.first = this.first.next;
    this.size--;
    return value;
  }
}

// Easy, but inefficient
export class StackWithArray<T> {
  private stack: CustomNode<T>[] = [];

  public push(value: T): void {
    this.stack.push(new CustomNode(value));
  }

  public pop(): T | undefined {
    return this.stack.pop()?.value;
  }
}
