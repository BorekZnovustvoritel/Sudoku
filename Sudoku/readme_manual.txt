
    S U D O K U
    ___________

Po spuštìní se zobratí hlavní menu. V hlavním menu se pohybujte smìrovımi
šipkami nahoru a dolù. Pro potvrzení vıbìru stisknìte enter. Pokud si pøejete
hru ukonèit, stiknìte escape. V menu se nacházejí následující monosti (pozn. 
monosti oznaèené hvìzdièkou * se zobrazí, jen pokud existuje rozehraná hra):

-1)* Continue
    Vyberte tuto monost, pokud si pøejete pokraèovat v rozehrané høe.
    
0)* Save the current game
    Uloí rozehranou hru. Hry se ukládají pøes hlavní menu, z rozehrané hry se
    do menu dostanete stiskem klávesy escape. Po vybrání této monosti bude
    program chtít, abyste zadali jméno uloené hry. Název volte libovolnı,
    vyvarujte se však ukládání her pod názvy '000.txt', '001.txt' a '002.txt',
    jinak by došlo ke smazání pùvodních souborù. Po zadání názvu se vytvoøí
    v adresáøi soubor s Vámi vybranım jménem. Tento soubor obsahuje Vámi
    uloenou hru. Soubor se nesmae ani po ukonèení programu.
                 
1) Start a new game
    Vıbìrem této monosti se spustí nová hra uloená v souboru pojmenovaném
    000.txt. Hru lze kdykoli úøerušit a uloit vıše zmínìnım postupem.

2) Load a saved game
    Pokud zvolíte tuto monost, budete dotázáni, abyste zadali jméno uloené
    hry, kterou chcete naèíst. Pokud nemáte vlastní rozehranou hru, kterou byste
    chtìli vyzkoušet naèíst, v adresáøi jsou umístìné 3 soubory:
        001.txt
        002.txt
        003.txt
    Po zadání jednoho z tìchto dvou názvù (vèetnì pøípony) se zobrazí hrací
    pole. I tuto hru je mono pøerušit a uloit.
    Pomocí této monosti se takté otevírají soubory s hracím polem definovanım
    uivatelem. Je potøeba toto hrací pole jen umístit do adresáøe tohoto
    programu a správnì zadat název souboru, ve kterém se hrací pole nachází.

3) Create a new layout
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

 