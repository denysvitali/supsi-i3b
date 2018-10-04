package blocks;

import drawing.PixelMap;

public class HorizBlock extends AbstractBlock {
	private AbstractBlock left, right;

	public HorizBlock(AbstractBlock left, AbstractBlock right){
		this.left = left;
		this.right = right;
	}

	@Override
	public int getWidth() {
		return left.getWidth() + right.getWidth();
	}

	@Override
	public int getHeight() {
		return Math.max(left.getHeight(), right.getHeight());
	}

	@Override
	public void draw(PixelMap pm, int originX, int originY) {
		this.left.draw(pm, originX, originY);
		this.right.draw(pm, originX + left.getWidth(), originY);
	}
}
