package pong;

import java.awt.Color;
import java.awt.Graphics;

public class enemy {

	public double x,y;
	public int width,height;
	
	public enemy(int x, int y) {
		this.x = x;
		this.y = y;
		this.width = 40;
		this.height = 5;
	}
	
	public void tick() {
		x+= (Game.ball.x - x - 6) * 0.07; 
		
	}

	public void render(Graphics g) {
		g.setColor(Color.magenta);
		g.fillRect((int)x, (int)y, width, height);
	}
}
