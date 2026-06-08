import { List } from "./list.js";
import { Stack } from "./stack.js";

function loopList<T>(list: List<T>) {
  let tempNode = list.head;
  while (tempNode) {
    console.log(tempNode.value);
    tempNode = tempNode.next;
  }
}

function loopStack<T>(stack: Stack<T>) {
  let tempNode = stack.head;
  while (tempNode) {
    console.log(tempNode.value);
    tempNode = tempNode.next;
  }
}

function main() {
  const list = new List<number>();
  list.push(1);
  list.push(2);
  list.push(3);
  list.push(4);
  list.push(5);
  list.push(6);
  list.push(7);
  list.push(8);
  list.push(9);
  list.push(10);

  loopList(list);

  list.pop();
  console.log("After pop:");
  loopList(list);

  list.shift();
  console.log("After shift:");
  loopList(list);

  list.unshift(0);
  console.log("After unshift:");
  loopList(list);

  const node = list.get(0);
  console.log(node);

  list.reverse();
  console.log("After reverse:");
  loopList(list);

  const mainStack = new Stack<number>();

  mainStack.push(1);
  mainStack.push(2);
  mainStack.push(3);
  mainStack.push(4);
  mainStack.push(5);
  mainStack.push(6);
  mainStack.push(7);
  mainStack.push(8);
  mainStack.push(9);
  mainStack.push(10);

  console.log("Main stack:");
  loopStack(mainStack);
  console.log("Main stack pop:", mainStack.pop());
  console.log("Main stack:");
  loopStack(mainStack);
  return 0;
}

main();
