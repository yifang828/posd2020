class TwoDimensionalCoordinate{
public:
  TwoDimensionalCoordinate(double x, double y){
      _x = x;
      _y = y;
  }

  double getX() {
      return _x;
  }
  double getY() {
      return _y;
  }

private:
  double _x, _y;
};