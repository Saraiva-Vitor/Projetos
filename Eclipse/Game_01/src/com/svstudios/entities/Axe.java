package com.svstudios.entities;

import java.awt.image.BufferedImage;

public class Axe extends Entity{

	public Axe(int x, int y, int width, int height, BufferedImage sprite) {
		super(x, y, width, height, sprite);
		
		depth = 0;
	}

}
