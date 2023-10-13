class Singly_linked_list{
	

       private class Node{
		int element;
		Node next;
		private Node(){}

		private Node(int element1){
			this.element = element1;	
		}
	}

	Node head = new Node();

	public Singly_linked_list(){}

	public void push(int element){
		Node newNode = new Node(element);
		newNode.next = head.next;
		if(head!=null){
		newNode.next = head.next;
		}
		if(head==null){
		newNode.next = null;
		}
		head = newNode;	
	}
	public int pop(){
		if(head!=null){
		Node tmp = head;
		head = tmp.next;
		return tmp.element;
		}
		if(head==null){
		System.out.println("fuck");
		}
		
	}
