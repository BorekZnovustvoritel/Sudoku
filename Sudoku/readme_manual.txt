
    S U D O K U
    ___________

Po spuštìní se zobratí hlavní menu. V hlavním menu se pohybujte smìrovımi
šipkami nahoru a dolù. Pro potvrzení vıbìru stisknìte enter. Pokud si pøejete
hru ukonèit, stiknìte escape. V menu se nacházejí následující monosti (pozn. 
monosti oznaèené hvìzdièkou * se zobrazí, jen pokud existuje rozehraná hra):

1)* Continue
    Vyberte tuto monost, pokud si pøejete pokraèovat v rozehrané høe.
    
2)* Save the current game
    Uloí rozehranou hru. Hry se ukládají pøes hlavní menu, z rozehrané hry se
    do menu dostanete stiskem klávesy escape. Po vybrání této monosti bude
    program chtít, abyste zadali jméno uloené hry. Název volte libovolnı,
    vyvarujte se však ukládání her pod názvy '001.txt', '002.txt' a '003.txt',
    jinak by došlo ke smazání pùvodních souborù. Po zadání názvu se vytvoøí
    v adresáøi soubor s Vámi vybranım jménem. Tento soubor obsahuje Vámi
    uloenou hru. Soubor se nesmae ani po ukonèení programu.
                 
3) Start a new game
    Po zvolení této monosti vyberte pomocí smìrovıch šipek obtínost. Následnì
    se vygeneruje pole podle Vámi zadané úrovnì obtínosti. Hru lze kdykoli
    pøerušit a uloit vıše zmínìnım postupem.

4) Load a saved game
    Po zvolení této monosti se zobrazí monosti na spuštìní hry manuálním
    zadáním jejího názvu, nebo vyuít jednu z posledních uloenıch her. Pokud
    byste omylem zavøeli aplikaci, kde jste mìli rozehranou hru, bude uloená
    pod názvem Last exit-game cache. ádná data tedy nebudou ztracena. Hry lze
    naèítat pouze z adresáøe Playgrounds.

5) Create a new layout
    Tato monost Vám umoní pøímo v konzoli vytváøet nové hrací pole. Pokud jste
    s hracím polem spokojeni, stisknìte klávesu escape. Zadejte název Vašeho
    nového hracího pole. Následnì se hrací pole uloí. Otevøít jej lze opìt
    pomocí monost 'Load a saved game'.
    
4) Exit
    Stejnì jako stisknutí klávesy escape v hlavním menu tato monost ukonèí
    program.
________________________________________________________________________________
    
Formát vkládání externích hracích polí:
1) Vytvoøte v adresáøi programu novı textovı soubor. Název souboru by nemìl
    obsahovat diakritiku.
2) Zapisujte èísla vdy 9 na øádek. Pokud má bıt v hracím poli prázdné místo,
    nahraïte jej NULOU, ne mezerou. Ani èísla, která jsou vedle sebe na øádku
    NEODDÌLUJTE mezerou. Pouívejte jen èísla, ádné jiné znaky. Kadı novı
    øádek zaènìte stisknutím klávesy enter, ádné jiné formátovací klávesy
    nepouívejte.
3) Nyní mùete pole buï rovnou naèíst (viz pøíští krok), nebo jej mùete
    v textovém editoru ještì celé zkopírovat a vloit jeho kopii za toto pole.
    Hra naèítá pole do pamìti dvakrát, jednou jako referenci a podruhé
    pro všechny hodnoty, tedy i hráèem vyplnìnıch. Program je ale ošetøen tak,
    e pokud dostane jen jedno hrací pole, sám jej zkopíruje do této hráèem
    upravovatelné pamìti.
4) Zavøete editor textového souboru a spuste program. Zvolte monost 'Load
    a saved game' a vlote název souboru. Nezapomeòte na pøíponu .txt. Takto
    rozehranou hru lze standartním zpùsobem uloit. 

 