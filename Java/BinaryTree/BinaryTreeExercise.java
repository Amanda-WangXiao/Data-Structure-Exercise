class BinaryTreeExercise {
	public static void main(String[] args) {
		
		TreeNode root = new TreeNode(1, "num-1");
		TreeNode node2 = new TreeNode(2, "num-2");
		TreeNode node3 = new TreeNode(3, "num-3");
		TreeNode node4 = new TreeNode(4, "num-4");
		TreeNode node5 = new TreeNode(5, "num-5");
		TreeNode node6 = new TreeNode(6, "num-6");
		
		root.setLeft(node2);
		root.setRight(node3);
		
		node2.setLeft(node4);
		node2.setRight(node5);
		
		node3.setRight(node6);
		
		BinaryTree binaryTree = new BinaryTree(root);
		System.out.println("preOrder: ");
		binaryTree.preOrder();
		
		System.out.println("infixOrder: ");
		binaryTree.infixOrder();
		
		System.out.println("postOrder: ");
		binaryTree.postOrder();
	}
}

class BinaryTree{
	private TreeNode root;
	
	public BinaryTree(TreeNode root){
		this.root = root;
	}
	
	public void preOrder(){
		this.root.preOrder();
	}
	public void infixOrder(){
		this.root.infixOrder();
	}

	public void postOrder(){
		this.root.postOrder();
	}

}

class TreeNode{
	private int no;
	private String info;
	private TreeNode left;
	private TreeNode right;
	
	public TreeNode(){
			this.no = -1;
			this.info = "default";
		}
		
	public TreeNode(int no,String info){
		this.no = no;
		this.info = info;
	}
	
	public int getNo() {
		return no;
	}

	public void setNo(int no) {
		this.no = no;
	}

	public String getInfo() {
		return info;
	}

	public void setInfo(String info) {
		this.info = info;
	}

	public TreeNode getLeft() {
		return left;
	}

	public void setLeft(TreeNode left) {
		this.left = left;
	}

	public TreeNode getRight() {
		return right;
	}

	public void setRight(TreeNode right) {
		this.right = right;
	}

	public String toString() {
		return "TreeNode{" +
				"no=" + no +
				", info='" + info + '\'' +
//				", left=" + left +
//				", right=" + right +
				'}';
	}
	
	public void preOrder(){
		System.out.println(this);
		if(this.left != null) this.left.preOrder();
		if(this.right != null) this.right.preOrder();
	}

	public void infixOrder(){
		if(this.left != null) this.left.infixOrder();
		System.out.println(this);
		if(this.right != null) this.right.infixOrder();
	}

	public void postOrder(){
		if(this.left != null) this.left.postOrder();
		if(this.right != null) this.right.postOrder();
		System.out.println(this);
	}
	
}

