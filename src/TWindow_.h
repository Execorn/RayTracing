#pragma once

#include <SFML/Graphics.hpp>
#include "TVector_.h"
#include "TLine_.h"
#include "TCoordSys_.h"
#include "TEvent_.h"
#include "TVertex_.h"

// ----------------------------------------------------------------

class TWindow_ {

private:
	size_t width_, height_;

	sf::RenderWindow window_;
	
public:
	TWindow_(size_t width, size_t height, std::string winname = "Window!");

	bool isOpen() const {
		return window_.isOpen();
	}

	bool getPollEvent(TEvent_* expectedEvent);

	//void render(const  	 TCoordSys_& 	coordSys_) const;
	void render(const        TLine_& 	       line);
	void render(const  	  Vector2f_&	     vector);
	void render(Tvertex_* points, size_t vertex_cnt);

	void resize(size_t width, size_t height);
    void clear(TColor_ background_color);
    void display();
	void close();

    ~TWindow_();
};

// ----------------------------------------------------------------