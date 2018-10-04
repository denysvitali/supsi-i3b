package blocks;

import drawing.PixelMap;

public class Block extends AbstractBlock {
	private int width, height;

	public Block(int width, int height){
		this.width = width;
		this.height = height;
	}

	@Override
	public int getWidth() {
		return width;
	}

	@Override
	public int getHeight() {
		return height;
	}

	@Override
	public void draw(PixelMap pm, int originX, int originY) {
		pm.drawRect(originX, originY, width, height);
	}
}
