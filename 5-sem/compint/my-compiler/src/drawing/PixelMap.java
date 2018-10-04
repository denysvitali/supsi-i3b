package drawing;

public class PixelMap {
	private char[][] map;

	private static char DECORATOR_CROSS = '+';
	private static char DECORATOR_VERT = '|';
	private static char DECORATOR_HORIZ = '-';

	public PixelMap(int width, int height){
		map = new char[height][width];

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
				map[i][j] = ' ';
			}
		}
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<map.length; i++){
			for(int j=0; j<map[i].length; j++){
				sb.append(map[i][j]);
			}
			sb.append(System.getProperty("line.separator"));
		}
		return sb.toString();
	}

	void drawHLine(int x, int y, int x_end){
		for(int i=x; i<= x_end; i++){
			if(map[y][i] == DECORATOR_VERT  | map[y][i] == DECORATOR_CROSS){
				map[y][i] = DECORATOR_CROSS;
			} else {
				map[y][i] = DECORATOR_HORIZ;
			}
		}
	}

	void drawVLine(int x, int y, int y_end){
		for(int i=y; i<= y_end; i++){
			if(map[i][x] == DECORATOR_HORIZ | map[i][x] == DECORATOR_CROSS){
				map[i][x] = DECORATOR_CROSS;
			} else {
				map[i][x] = DECORATOR_VERT;
			}
		}
	}

	public void drawRect(int x, int y, int w, int h) {
		// TOP
		drawHLine(x, y, x + w);
		// BOTTOM
		drawHLine(x, y + h, x + w);
		// LEFT
		drawVLine(x, y, y + h);
		// RIGHT
		drawVLine(x + w, y, y + h);
	}
}
