export class CustomNode<T> {
  public next: CustomNode<T> | null = null;
  constructor(public value: T) {}
}
