#pragma once
#include "kernel.hpp"
#include "math.h"

inline void Logo(Framebuffer* fb, FONT* font){

    for(int i = 0; i < 1e+9; i++){} //1 second in nanoseconds

	println();
	println();
	Print(fb, font, 0xFFFDD0, "   ____                         ___  ____  ");
	println(); 
 	Print(fb, font, 0xFFFDD0, " / ___|_   _  __ ___   ____ _ / _ \\/ ___| ");
	println(); 
 	Print(fb, font, 0xFFFDD0, "| |  _| | | |/ _` \\ \\ / / _` | | | \\___ \\");
	println(); 
 	Print(fb, font, 0xFFFDD0, "| |_| | |_| | (_| |\\ V / (_| | |_| |___) |");
	println(); 
 	Print(fb, font, 0xFFFDD0, " \\____|\\__,_|\\__,_| \\_/ \\__,_|\\___/|____/");
	println(); 
	println();

	Print(fb, font, 0xFFFDD0, "					..ohhhhyoo+/:```     						   		   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                    `::hNNNNNMMNmd//.``           						   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                     ..ohhmmNMMMMNmmo--                					   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                       `....:++mNNMMmdd``                   			   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                            `..osyMMMMM--.                       		   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                               --/MMMMM++:``                          	   ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                             ``--/mmNMMdds::.``                            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                          //+yydmmNNMMMNNNmmhhy++-                         ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                     ``:++hhdNNMMMNNNNNNNNMMNNNddsoo```                    ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                    `--sddMMMNNmmmhhhhhhhdmmNNNMMNNN//-                    ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                  ``-mmNMMNNmdd/:-```````.--shhNNMMMMMy--`                 ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                  +osNNMMMss+::...```````...--:oodMMMMmyy.                 ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                ``ydmMMmdd::-`````````````````.--ohhMMNmm/--               ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               `--dNMMMhss```````````````````````://NNNMMso+               ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               -ssNMMNN+..``````````````````````````ddmMMmdy               ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               :ddNMNhh/````````````````````````````oohMMNNh               ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               /mmMMNss:``````````````````````````..::sMMMMd``             ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               /NNMMNoo:``````````````````````````..--oMMMMm..`            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               /NNMMmoo:````````````````````````````..oMMMMm--`            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "               /NNMMmoo:..``````````````````````````..oNNMMm::.            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "             ``+NNMMm++-..``````````````````````````..+NNMMm++.            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "             ..oMMMMm::-..````````````````````````````/mmNMNss-            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "             //yMMMMd...``````````````````````````````/hhNMMmm/            ");
	println(); 
	Print(fb, font, 0xFFFDD0, "           ``NNNMMdhs`````````````````````````````````:oomMMMMo..          ");
	println(); 
	Print(fb, font, 0xFFFDD0, "          .::MMMMMs+/`````````````````````````````````.::dNNMMhss          ");
	println(); 
	Print(fb, font, 0xFFFDD0, "        ..+yyMMNNN/--::://```````````````````````---//:..yddMMNmm--.       ");
	println(); 
	Print(fb, font, 0xFFFDD0, "       `//hMMMMmhh-.-sshdd...````````````````````/oodds../+oMMMMMyy/``     ");
	println(); 
	Print(fb, font, 0xFFFDD0, "     ..:NNMMMMMy---:+MMMMM//:`````````````````...yMMMMdoo-.-ddNMMMMd++`    ");
	println(); 
	Print(fb, font, 0xFFFDD0, "     osyMMMNN++:../+sMMMMMyy+`````````````````.::hMMMMmhh-`.::ymmMMNdd-``  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "   ``hmmMMmhh...``:/+ddNMMddo`````````````````.--sddMMNdd-``../ssMMMNN+/:  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "  `::mMMMMy++`````..-ssdMMNNs..``````````````````/ooNNNmm-``.....NNNMMhyo  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "  :yyNMNmm+..`````..-ssdMMNNy..``````````````````:++MMNmm-```````yydMMmmy  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "  /mmMMNyy/```````/+ommNMMddo`````````````````.::ymmMMNdd-`````..++yMMNNh  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "``/NNMMNss:```````/+oMMMMMss/`````````````````.::hMMMMmyy-````...::sMMMNd``");
	println(); 
	Print(fb, font, 0xFFFDD0, "``+NNMMNoo:`````..--/NNNNN::-`````````````````...sNNNNh++.`````..--oMMMMd``");
	println(); 
	Print(fb, font, 0xFFFDD0, "``+NNMMNoo:`````````-ooyyy...````````````````````/oohho...`````..::sMMMMd``");
	println(); 
	Print(fb, font, 0xFFFDD0, "  /mmNMNyy:`````````...---```````````````````````...--...``````..++yMMNNh  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "  :yyNMNdd/..````````````````````````````````````````````````````yydMMmmh  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "  .//mMMNNo::`````````````````````````````````````````````````...mmNMMdhs  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "   ``dNNMMdhh```````````````````````````````````````````````..://MMMMMs+/  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "     syhMMNNN++:..`````````````````````````````````````````.::ymmMMNmm:``  ");
	println(); 
	Print(fb, font, 0xFFFDD0, "     -:+mmNMMddy++---...........-........................:/+yymMMMMdoo.    ");
	println(); 
	Print(fb, font, 0xFFFDD0, "       .yydNNMMNddo++::::::::///+/::::::::///+/:::::::///yhhMMMMMdds--`    ");
	println(); 
	Print(fb, font, 0xFFFDD0, "        ``+hhNNNMMMMMMMNNNMMMMMMMMMMNNNMMMMMMMMMMNNNMMMMMMMMNNNNN--.       ");
	println(); 
	Print(fb, font, 0xFFFDD0, "          .--ooymmMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNyy+::``        ");
	println(); 
	Print(fb, font, 0xFFFDD0, "             ..:++ssyhhhhhhhhyyyyyhhhhhhhhyyyyyhhhhhhhhyyoo+::.``          ");
	println(); 
	Print(fb, font, 0xFFFDD0, "                  .--////////::--:////////:::-:////////::.`				   ");
	println();
}

inline void Copyright(Framebuffer* fb, FONT* font){
	CharPosition.X = 960;
	CharPosition.Y = -540;
	
	Print(fb, font, 0xFFFDD0, "Copyright © Marcelo Raul Rios Jr. 2022");
}