package shed;

import java.util.List;

import model.*;

public abstract class Tools {

	public static Ray[] quickSortRays(List<Ray> list) {
		return quickSort(list.toArray(new Ray[list.size()]), 0, list.size() - 1);
	}

	public static Ray[] quickSort(Ray[] arr, int begin, int end) {
    	if (begin < end) {
        	int partitionIndex = partition(arr, begin, end);

        	quickSort(arr, begin, partitionIndex-1);
        	quickSort(arr, partitionIndex+1, end);
    	}
    	return arr;
	}
	private static int partition(Ray[] arr, int begin, int end) {
		double pivot = angleFromPoint(arr[end].getDir());
		int i = (begin-1);

		for (int j = begin; j < end; j++) {
			if (angleFromPoint(arr[j].getDir()) <= pivot) {
				i++;
				Ray swapTemp = arr[i];
				arr[i] = arr[j];
				arr[j] = swapTemp;
	        }
	    }

		Ray swapTemp = arr[i+1];
		arr[i+1] = arr[end];
		arr[end] = swapTemp;	

		return i+1;
	}

	// public static double angleFromPoint(Point point) {
	// 	double angle = 0.0;
	// 	if (point.getX() == 0 && point.getY() == 0) {
	// 		return angle;
	// 	}
	// 	if (point.getX() > 0) {
	// 		if (point.getY() > 0) {
	// 			angle = Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
	// 		} else {
	// 			angle = 360.0 - Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
	// 		}
	// 	} else {
	// 		if (point.getY() > 0) {
	// 			angle = 180.0 - Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
	// 		} else {
	// 			angle = 180.0 + Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
	// 		}
	// 	}
		
	// 	return angle;
	// }
	public static double angleFromPoint(Point p) {
		Point p0 = new Point(0, 0);
        double x = p.getX() - p0.getX();
        double y = p.getY() - p0.getY();
        double angle = Math.toDegrees(Math.atan2(y, x));
        if (angle < 0) {
        	angle += 360;
        }
        return angle;
    }

	public static Point pointFromAngle(double i) {
		double x = Math.cos(Math.toRadians(i));
		double y = Math.sin(Math.toRadians(i));
		return new Point(x, y);
	}

}