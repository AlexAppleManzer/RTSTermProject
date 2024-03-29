# double determinant(double num1, double num2, double num3, double num4)
# {
# 	return num1 * num4 - num2 * num3;
# }

# bool intersect(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy) {
# 	double det1 = determinant(ax - cx, bx - cx, ay - cy, by - cy); // top left
# 	double det2 = determinant(cx - ax, dx - ax, cy - ay, dy - ay); // bottom left

# 	double det3 = determinant(ax - dx, bx - dx, ay - dy, by - dy); // top right
# 	double det4 = determinant(cx - bx, dx - bx, cy - by, dy - by); // bottom right

# 	if (std::signbit(det1) != std::signbit(det3) && std::signbit(det2) != std::signbit(det4)) {
# 		return true;
# 	}

# 	return false;
# }

def determinant(num1, num2, num3, num4):
    return num1 * num4 - num2 * num3

def intersect(ax, ay, bx, by, cx, cy, dx, dy):
    det1 = determinant(ax - cx, bx - cx, ay - cy, by - cy)
    det2 = determinant(cx - ax, dx - ax, cy - ay, dy - ay)
    det3 = determinant(ax - dx, bx - dx, ay - dy, by - dy)
    det4 = determinant(cx - bx, dx - bx, cy - by, dy - by)

    sign1 = det1 > 0
    sign2 = det2 > 0
    sign3 = det3 > 0
    sign4 = det4 > 0

    if (sign1 != sign3 and sign2 != sign4):
        return True
    return False
