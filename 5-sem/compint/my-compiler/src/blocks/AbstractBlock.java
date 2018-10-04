package blocks;

import drawing.PixelMap;

public abstract class AbstractBlock {
	private int width, height;

	public abstract int getWidth();
	public abstract int getHeight();
	public abstract void draw(PixelMap pm, int originX, int originY);
}
