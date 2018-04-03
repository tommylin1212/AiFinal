#include "polylinepic.h"

using namespace std;
polylinepic::polylinepic() {
	//nothing to do here :)
}

polylinepic::polylinepic(string file) {
	std::ifstream fin;
	fin.open(file);
	if (fin.fail()) {
		cout << "Failed to open " << file << endl;
		exit(1);
	}
	int num_lines, num_points;
	GLdouble x_val, y_val;
	fin >> num_lines;
	for (int ln = 0; ln < num_lines; ln++) {
		polyline poly;
		fin >> num_points;
		for (int pnt = 0; pnt < num_points; pnt++) {
			fin >> x_val >> y_val;
			point p(x_val, y_val, 0);
			poly.add(p);

			if (ln == 0 && pnt == 0) { // first point read
				m_left = x_val;
				m_right = x_val;
				m_bottom = y_val;
				m_top = y_val;
			}
			if (x_val < m_left) m_left = x_val;
			if (x_val > m_right) m_right = x_val;
			if (y_val < m_bottom) m_bottom = y_val;
			if (y_val > m_top) m_top = y_val;
		}
		m_polylines.push_back(poly);
	}
}
void polylinepic::add(polyline po) {
	m_polylines.push_back(po);
}

void polylinepic::plot() {
	for (vector<polyline>::iterator i = m_polylines.begin(); i < m_polylines.end(); i++) {
		i->plot();
	}
}

void polylinepic::openfile(string file) {
	std::ifstream fin;
	int num_lines, num_points;
	GLdouble x_val, y_val;
	std::string in;

	fin.open(file);
	if (fin.fail()) {
		std::cout << "Failed to open " << file << std::endl;
		exit(1);
	}
	do {
		getline(fin, in);
	} while (in[0] != '*');
	//getline(fin, in);

	// read extent info
	// left, top, right, bottom
	fin >> m_left >> m_top >> m_right >> m_bottom;

	fin >> num_lines;
	for (int ln = 0; ln < num_lines; ln++) {
		polyline poly;
		fin >> num_points;
		for (int pnt = 0; pnt < num_points; pnt++) {
			fin >> x_val >> y_val;
			point p(x_val, y_val, 0);
			poly.add(p);
		}
		m_polylines.push_back(poly);
	}
}