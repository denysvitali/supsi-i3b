import blocks.Block;
import blocks.HorizBlock;
import blocks.VertBlock;
import drawing.PixelMap;

public class Main {
	public static void main(String[] args){
		PixelMap pm = new PixelMap(50, 50);

		VertBlock vb = new VertBlock(new Block(5, 3),
				new Block(7,2));
		VertBlock vb2 = new VertBlock(new Block(5, 3),
				new Block(7,2));
		HorizBlock hb2 = new HorizBlock(vb, vb2);

		hb2.draw(pm, 0, 0);

		System.out.println(pm);
	}
}
