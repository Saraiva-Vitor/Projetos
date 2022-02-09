package com.svstudios.graficos;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import com.svstudios.entities.Player;
import com.svstudios.main.Game;

public class UI {

	
	public void render(Graphics g) {
		g.setColor(Color.darkGray);
		g.fillRect(8,4,100,8);
		g.setColor(Color.red);
		g.fillRect(8,4,(int)(Game.player.life),8);
		g.setColor(Color.white);
		g.setFont(new Font("arial", Font.BOLD,9));
		g.drawString((int)Game.player.life+"/"+(int)Game.player.maxlife,40,11);
		
		g.setColor(Color.darkGray);
		g.fillRect(8,13,100,5);
		g.setColor(Color.green);
		g.fillRect(8,13,Player.stamina,5);
		g.setColor(Color.gray);
		g.setFont(new Font("arial", Font.BOLD,7));
		g.drawString(Player.stamina+"/"+Player.maxstamina,45,18);
	}
	
}
