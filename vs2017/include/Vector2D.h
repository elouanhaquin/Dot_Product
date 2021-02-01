#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>


#define PI 3.14159f

template <typename T>
class Vector2D
{
private:
	T x;
	T y;
	T z;
public:

	//BUILD FONCTION
	Vector2D() { this->x = 0; this->y = 0; this->z = 0; }
	Vector2D(bool isMadeWithAngle, T m_x, T m_y, T m_z) 
	{
		if (isMadeWithAngle) 
		{
			this->x = m_x * cos(m_y* (PI / 180)) ;
			this->y = m_x * sin(m_y* (PI / 180)) ;
			
		} 
		else
		{
			this->x = m_x; 
			this->y = m_y;
			this->z = m_z;
		} 
	}



	Vector2D(Vector2D& other) { this->set_X(other.X());  this->set_Y(other.Y()); this->set_Z(other.Z());}
	Vector2D(const sf::Vector2i& other) { this->set_X(other.x); this->set_Y(other.y); this->set_Z(0);}
	Vector2D(const sf::Vector2f& other) { this->set_X(other.x); this->set_Y(other.y); this->set_Z(0); }
	~Vector2D() {};

	//GETTERS

	T X()const { return this->x; }
	T Y()const { return this->y; }
	T Z()const { return this->z; }

	//SETTERS

	void set_Y(T m_y) { this->y = m_y; }
	void set_X(T m_x) { this->x = m_x; }
	void set_Z(T m_z) { this->z = m_z; }

	//OVERLOADING OPERATORS

	Vector2D& operator=(const Vector2D& other) { this->set_X(other.X()); this->set_Y(other.Y()); this->set_Z(other.Z()); return *this; }
	Vector2D& operator=(Vector2D& other) {this->set_X(other.X()); this->set_Y(other.Y()); this->set_Z(other.Z()); return *this; }
	
	
	Vector2D operator*(const Vector2D& other) { Vector2D<float> vec1(false, 0, 0,0); vec1.set_X(other.X() * this->X()); vec1.set_Y(other.Y() * this->Y());  vec1.set_Z(other.Z() * this->Z()); return vec1; }
	Vector2D operator+(const Vector2D& other) { Vector2D<float> vec1(false, other.X() + this->X(), other.Y() + this->Y(), other.Z() + this->Z()); return vec1; }
	Vector2D operator-(const Vector2D& other) { Vector2D<float> vec1(false, 0, 0, 0); vec1.set_X(this->X() - other.X()); vec1.set_Y(this->Y() - other.Y());  vec1.set_Z(other.Z() - this->Z()); return vec1; }
	Vector2D operator-(const sf::Vector2f& other) { Vector2D<float> vec1(false, 0, 0, 0); vec1.set_X(this->X() - other.x); vec1.set_Y(this->Y() - other.y);  vec1.set_Z(0); return vec1; }
	Vector2D operator*(float scalaire) { Vector2D<float> vec1(false, 0, 0, 0); vec1.set_X(this->X() * scalaire); vec1.set_Y(this->Y() * scalaire); vec1.set_Z(this->Z() * scalaire); return vec1; }
	Vector2D operator+(float scalaire) { Vector2D<float> vec1(false, 0, 0, 0); vec1.set_X(this->X() + scalaire); vec1.set_Y(this->Y() + scalaire); vec1.set_Z(this->Z() + scalaire); return vec1; }
	Vector2D operator-(float scalaire) { Vector2D<float> vec1(false, 0, 0, 0); vec1.set_X(this->X() - scalaire); vec1.set_Y(this->Y() - scalaire); vec1.set_Z(this->Z() - scalaire); return vec1; }
	
	

	//VECTORS THINGS



	int angle_Rotate(Vector2D& vec1)
	{ 
		float vecAngleX = this->X() - vec1.X() ;
		float vecAngleY = this->Y() - vec1.Y();
		return -atan2(vecAngleX, vecAngleY) * 180 / PI;			//Thanks to Max 
	}
	float angle_With(Vector2D& vec1)
	{
		
		float dot_product = this->dot_product(vec1);
		float length = this->get_Norme() * vec1.get_Norme();
		return acos(dot_product / length) * (180 / PI);
	}

	long int scalar_Between(Vector2D& vec1) { return (vec1.X() * this->X()) + (vec1.getY() * this->Y()); }
	long double get_Norme() { return sqrt((this->X()*this->X()) + (this->Y()*this->Y()) + (this->Z()*this->Z())); }
	
	void normalize() { double length = this->get_Norme(); this->set_X(this->X() / length);  this->set_Y(this->Y() / length);}
	
	int dot_product(Vector2D& vec1) {int i = 0; i = this->x * vec1.X() + this->y * vec1.Y() + this->z * vec1.Z(); return  i;}

	sf::Vector2f& toSfVector() {return sf::Vector2f(this->X(), this->Y()); }
	sf::Vector2i& toSiVector() { return sf::Vector2i(this->X(), this->Y()); }

	//TEST FUNCTIONS

	bool isPerpendicular(Vector2D& vec2) { if (angle_With(this, vec2) == 90)return true; return false; }
	bool isNull() { if (this.X() == 0 && this.Y() == 0)return true; return false; }
	bool isParallel(Vector2D& vec2) { if (this->X() / vec2.X() == this->Y() / vec2.Y())return true; return false; }
	bool isOpposed(Vector2D& vec2) { if (this->isParallel(vec2) && this->X() + vec2.X() < this->X() && this->Y() + vec2.Y() < this->Y())return true; return false; }
	bool isNormalised() { if (this->get_Norme() == 1) { return true; } else return false; }
};


template <typename T>
std::ostream& operator<<(std::ostream& stream, Vector2D<T> & vec) { stream << vec.X() << " " << vec.Y() << " "  << vec.Z(); return stream; }