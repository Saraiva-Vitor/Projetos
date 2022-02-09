package com.svstudios.entities;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import com.svstudios.main.Game;

public class Npc extends Entity{

	public String[] frases = new String[5];
	
	public boolean showMessage = false;
	public boolean show = false;
	
	public int curIndexMsg = 0;
	
	public int fraseIndex = 0;
	
	public int time = 0, maxTime = 5;
	
	public Npc(int x, int y, int width, int height, BufferedImage sprite) {
		super(x, y, width, height, sprite);
		frases[0] = "Olá! Seja bem vindo ao tutorial.";
		frases[1] = "Utilize as teclas W A S e D para andar!";
		frases[2] = "Utilize também o mouse para a direção";
		frases[3] = "do ataque e o clique esquerdo para";
		frases[4] = "atacar!";
	}
	
	public void tick() {
		int xPlayer = Game.player.getX();
		int yPlayer = Game.player.getY();

		int xNpc = (int)x;
		int yNpc = (int)y;
		
		if(Math.abs(xPlayer-xNpc) < 20 && Math.abs(yPlayer - yNpc) < 20) {
			if(show == false) {
				showMessage = true;
				show = true;
			}
		}else {
			//showMessage = false;
		}
		
		
		
		if(showMessage) {
			
			time++;
			if(this.time >= maxTime) {
				time = 0;
				if(curIndexMsg < frases[fraseIndex].length()) {
					curIndexMsg++;	
				}else {
					if(fraseIndex < frases.length-1) {
						fraseIndex++;
						curIndexMsg = 0;
					}
				}
			}
		}
	}
	
	public void render(Graphics g) {
		super.render(g);
		if(showMessage){
			Color grayT = new Color(105, 105, 105, 127);
			Color blackT = new Color(0,0,0, 127);
			g.setColor(blackT);
			g.fillRect(2, 108, Game.WIDTH - 4, 50);
			g.setColor(grayT);
			g.fillRect(4, 110, Game.WIDTH - 8, 46);
			g.setFont(new Font("Arial", Font.BOLD,9));
			g.setColor(Color.white);
			g.drawString(frases[fraseIndex].substring(0,curIndexMsg), 48, 120);
			
			g.drawString(">Pressione enter para fechar<", 48, 120 + 8);
		}
	}

}
