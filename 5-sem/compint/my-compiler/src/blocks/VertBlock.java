package blocks;

import drawing.PixelMap;

public class VertBlock extends AbstractBlock {
	private AbstractBlock top, bottom;

	public VertBlock(AbstractBlock top, AbstractBlock bottom){
		this.top = top;
		this.bottom = bottom;
	}

	@Override
	public int getWidth() {
		return Math.max(top.getWidth(), bottom.getWidth());
	}

	@Override
	public int getHeight() {
		return top.getHeight() + bottom.getHeight();
	}

	@Override
	public void draw(PixelMap pm, int originX, int originY) {
		top.draw(pm, originX, originY);
		bottom.draw(pm, originX, originY + top.getHeight());
	}
}
