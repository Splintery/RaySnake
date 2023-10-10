package constant;

import model.Point;

public class Constant {
	public static final int BLOCK_SIZE = 16;
	public static final double WIDTH = 90;
	public static final double HEIGHT = 45;
	public static final int WINDOW_WIDTH = (int) (WIDTH * BLOCK_SIZE);
	public static final int WINDOW_HEIGHT = (int) (HEIGHT * BLOCK_SIZE);

	


	public static Point convertToPixels(Point convertMe) {
		double x = (convertMe.getX() * BLOCK_SIZE) + ((double) WINDOW_WIDTH) / 2;
		double y = (-convertMe.getY() * BLOCK_SIZE) + ((double) WINDOW_HEIGHT) / 2;

		return new Point(x, y);
	}
	public static Point convertToModel(Point convertMe) {
		double x = (convertMe.getX() - (double) WINDOW_WIDTH / 2) / BLOCK_SIZE;
		double y = -(convertMe.getY() - (double) WINDOW_HEIGHT / 2) / BLOCK_SIZE;

		return new Point(x, y);
	}
}