package constant;

import model.Point;

public class Constant {
	public static final int BLOCK_SIZE = 16;
	public static final int WINDOW_WIDTH = 1440;
	public static final int WINDOW_HEIGHT = 720;

	public static final double WIDTH = (double) WINDOW_WIDTH / BLOCK_SIZE;
	public static final double HEIGHT = (double) WINDOW_HEIGHT / BLOCK_SIZE;


	public static Point convertToPixels(Point convertMe) {
		double x = (convertMe.getX() * BLOCK_SIZE) + ((double) WINDOW_WIDTH / 2);
		double y = (-convertMe.getY() * BLOCK_SIZE) + ((double) WINDOW_HEIGHT / 2);

		return new Point(x, y);
	}
	public static Point convertToModel(Point convertMe) {
		double x = (convertMe.getX() - (double) WINDOW_WIDTH / 2) / BLOCK_SIZE;
		double y = -(convertMe.getY() - (double) WINDOW_HEIGHT / 2) / BLOCK_SIZE;

		return new Point(x, y);
	}
}