import { CustomNode } from "./nodes.ts";

export class List<T> {
  public head: CustomNode<T> | null = null;
  public tail: CustomNode<T> | null = null;
  public length = 0;

  constructor(firstNode?: T) {
    if (firstNode) {
      this.push(firstNode);
    } else {
      this.head = null;
    }
  }

  public push(value: T): this {
    const newNode = new CustomNode(value);

    if ((!this.head && !this.tail) || !this.head) {
      this.head = newNode;
      this.tail = newNode;
    } else {
      this.tail!.next = newNode;
      this.tail = newNode;
    }
    this.length++;
    return this;
  }

  public unshift(value: T): this {
    const newNode = new CustomNode(value);
    if (!this.head) {
      this.head = newNode;
      this.tail = newNode;
    } else {
      newNode.next = this.head;
      this.head = newNode;
    }
    this.length++;
    return this;
  }

  public pop() {
    if (this.length <= 0) return;

    let prevNode: CustomNode<T> | null = null;
    let curNode = this.head;

    while (curNode && curNode !== this.tail) {
      prevNode = curNode;
      curNode = curNode.next;
    }

    this.tail = prevNode as CustomNode<T>;
    this.tail.next = null;
    this.length--;
    return;
  }

  public shift() {
    if (!this.head) return;
    this.head = this.head.next;
    this.length--;
    // Como no tenemos manejo de memoria manual,
    // no es necesario borrar el anterior head. JS lo hace por mí
  }

  public get(index: number) {
    if (!this.head || index >= this.length || index < 0) return null;

    let curNode: CustomNode<T> = this.head;
    for (let i = 0; i < index; i++) {
      curNode = curNode.next as CustomNode<T>;
    }

    return curNode;
  }

  public set(index: number, value: T) {
    let node = this.get(index);
    if (node) {
      node.value = value;
      return true;
    }
    return false;
  }

  public insert(index: number, value: T) {
    if (!this.head || index < 0 || index > this.length) {
      return false;
    }

    if (index === 0) return !!this.unshift(value);
    if (index === this.length) return !!this.push(value);

    let newNode = new CustomNode(value);
    let prevNode: CustomNode<T> | null = this.get(index - 1);
    let curNode: CustomNode<T> | null = this.get(index);

    prevNode!.next = newNode;
    newNode.next = curNode;
    this.length++;
    return true;
  }

  public remove(index: number) {
    if (!this.head || index >= this.length || index < 0) return false;

    if (index === 0) {
      this.shift();
      return true;
    }

    if (index === this.length - 1) {
      this.pop();
      return true;
    }

    let prevNode: CustomNode<T> | null = this.get(index - 1);
    let curNode: CustomNode<T> | null = this.get(index);

    prevNode!.next = curNode!.next;
    this.length--;
    return true;
  }

  public reverse() {
    if (!this.head) return;
    let prev: CustomNode<T> | null = null;
    let node: CustomNode<T> | null = this.head;
    this.tail = node;
    let next: CustomNode<T> | null = null;

    // A -> B -> C -> null (Antes de iterar)
    while (node) {
      next = node.next; // Guardamos el siguiente nodo para las siguientes iteraciones (B -> C -> null)
      node.next = prev; // El valor anterior, cualquiera que sea, se pasa a ser el siguiente (A -> null)
      prev = node; // El nodo anterior pasa a ser el actual. (A(cur) -> A(prev) -> null)
      node = next; // Para seguir la iteración, vamos al siguiente (A(cur) -> B)
    }

    // A -> null
    // B -> A -> null
    // C -> B -> A -> null (final)

    this.head = prev;
    this.tail = this.get(this.length - 1);
  }
}
