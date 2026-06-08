import { CustomNode } from "./nodes.js";

export class Queue<T> {
  private first: CustomNode<T> | null = null;
  private last: CustomNode<T> | null = null;
  protected size = 0;

  constructor(firstNode?: T) {
    if (firstNode) {
      this.enqueue(firstNode);
    } else {
      this.first = null;
    }
  }

  enqueue(value: T): number {
    const node = new CustomNode(value);

    if (!this.first) {
      this.first = node;
      this.last = node;
    } else {
      this.last!.next = node; // El siguiente del ultimo apunta al nuevo
      this.last = node; // El ultimo nodo apunta al nuevo
    }

    return ++this.size;
  }

  dequeue(): T | null {
    if (!this.first) return null;
    const value = this.first.value;
    this.first = this.first.next;
    this.size--;
    return value;
  }
}
