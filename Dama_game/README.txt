Ciao fazzi
butto qui un po’ di idee:

- per ora sono riuscito a far sì che appena schiacci newGame ti chiede la squadra e poi appena scegli la squadra 
  ti mette la scacchiera giusta. La cosa che non è bellissima è che proprio nell’istante iniziale i quadrati della griglia
  sono un po’ più piccoli, ma appena mette le pedine tutto va a posto (succede perchè quando dichiari i bottoni della griglia
  non puoi dargli l’altezza e la larghezza altrimenti si impalla dopo quando mette le pedine) (ma cmq questa è una cosa minore, 
  per ora va bene così)

- ho tolto i bottoni bianco e nero che non servono più

- ho tolto il bottone changeImage perchè la mia idea del funzionamento del gioco è questa:

	- scelgo squadra e lui ti mette le pedine giuste (questo è già fatto)
	- muove sempre il bianco primo, quindi o il giocatore o il PC (se è il pc allora lo fa subito quando 
	  mette le pedine all’inizio)
	- il giocatore fa la sua mossa clickando su due tasti
	- la mossa appare nel riquadro che c’è già (più avanti penseremo ad abbellirlo meglio)
	- ci deve essere un bottone (come enterMove) che una volta scritta la mossa manda la mossa a cpp
	- in cpp la mossa viene mandata a dama.exe e dama.exe ritorna le nuove posizioni insieme a due flag:
		- una $endgame che resta interna al programma e dice se la partita va avanti o no
		- l’altra dice se la mossa è consentita o no e stampa da qualche parte “Mossa non consentita!prova ancora!”

- sul dove stampare le cose pensavo ad avere un riquadro di log che occupa tutto il frame a destra in cui restano stampate
  le mosse del giocatore (e del PC) tipo “User: 3d in 4e” oppure “PC: 3d in 4e” o “mossa non consentita...”

	- forse qui si può pensare di dividere il frame di destra in due: 
		1) uno contiene solo il log e 
		2) l’altro contiene i bottoni enterMove e clearMove con il riquadro dove appare la mossa


ovviamente queste sono solo un po’ di idee a caso. 
Forse domani riesco a lavorarci un po’, ma poi fino al 25 non farò nulla!
...però non fare tutto tu se no io non mi diverto! ;)

