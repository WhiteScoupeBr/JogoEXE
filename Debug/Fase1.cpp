#include "Fase1.h"

Fase1::Fase1()
{
    background.loadFromFile("FundoMaior.png");
    textureApache.loadFromFile("SpriteApache.png");
    bar.loadFromFile("Saloon.png");
    chao.loadFromFile("chao.png");
    chao21.loadFromFile("chao21.png");
    cacto.loadFromFile("cacto.png");
    tnt.loadFromFile("tnt.png");
    bola.loadFromFile("bola.png");
    bala1.loadFromFile("bala.png");
    bala22.loadFromFile("bala2.png");
    jj.loadFromFile("jj.png");
    fonte.loadFromFile("Carnevalee Freakshow.ttf");
    buffer2.loadFromFile("Gun.wav");
    gun.setBuffer(buffer2);

    Vector2u textureSizeApache = textureApache.getSize();
    textureSizeApache.x/=8;
    textureSizeApache.y/=1;


    invChao.push_back(Plataforma(nullptr,Vector2f(10000.f,100.f),Vector2f(90.f,350.f)));

    invPlataforma.push_back(Plataforma(nullptr,Vector2f(400.f,1000.f),Vector2f(-200.f,-50.f)));
    invPlataforma.push_back(Plataforma(nullptr,Vector2f(400.f,1000.f),Vector2f(5400.f,-50.f)));

    plataformas.push_back(Plataforma(&chao,Vector2f(1000.f, 450.f), Vector2f(90.f, 200.f)));

    plataformas.push_back(Plataforma(&chao21,Vector2f(100.f,50.f),Vector2f(750.f,-100.f)));//1
    plataformas.push_back(Plataforma(&chao21,Vector2f(250.f,50.f),Vector2f(1100.f,-180.f)));//2
    plataformas.push_back(Plataforma(&chao21,Vector2f(100.f,50.f),Vector2f(1430.f,-100.f)));//3
    plataformas.push_back(Plataforma(&chao21,Vector2f(400.f,50.f),Vector2f(1820.f,-180.f)));//4
    plataformas.push_back(Plataforma(&chao21,Vector2f(500.f,50.f),Vector2f(2500.f,-230.f)));//5
    plataformas.push_back(Plataforma(&chao21,Vector2f(60.f,50.f),Vector2f(3000.f,-100.f)));//6
    plataformas.push_back(Plataforma(&chao21,Vector2f(60.f,50.f),Vector2f(3100.f,-180.f)));//7
    plataformas.push_back(Plataforma(&chao21,Vector2f(100.f,50.f),Vector2f(3400.f,-240.f)));//8
    plataformas.push_back(Plataforma(&chao21,Vector2f(400.f,50.f),Vector2f(3780.f,-240.f)));//9
    plataformas.push_back(Plataforma(&chao21,Vector2f(100.f,50.f),Vector2f(4200.f,-240.f)));//10
    plataformas.push_back(Plataforma(&chao21,Vector2f(100.f,50.f),Vector2f(4400.f,-200.f)));//11
    plataformas.push_back(Plataforma(&chao,Vector2f(1200.f,450.f),Vector2f(5150.f,200.f)));//12

    //obs.push_back((Obstaculo*)new Cacto(&cacto,Vector2f(46.f,80.f),Vector2f(200.f,-60.f)));
    obs.push_back((Obstaculo*)new Cacto(&cacto,Vector2f(46.f,80.f),Vector2f(470.f,-60.f)));
    obs.push_back((Obstaculo*)new Cacto(&cacto,Vector2f(46.f,80.f),Vector2f(3025.f,-160.f)));//1

    obs.push_back((Obstaculo*)new BolaFeno(&bola,Vector2f(30.f,30.f),Vector2f(3800.f,-290.f)));//1

    obs.push_back((Obstaculo*)new Tnt(&tnt,Vector2f(30.f,30.f),Vector2f(1170.f,-215.f)));//1



    inimigos.push_back((Inimigo*)new Apache(&textureApache,Vector2f(2500.f,-300.f),Vector2u(8,1),0.1f));//1
    inimigos.push_back((Inimigo*)new Apache(&textureApache,Vector2f(3550.f,-310.f),Vector2u(8,1),0.1f));//2
    inimigos.push_back((Inimigo*)new Apache(&textureApache,Vector2f(4620.f,-70.f),Vector2u(8,1),0.1f));//3

    inimigos.push_back((Inimigo*)new JJ(&jj,Vector2f(750.f,-170.f),0.1f));//1
    inimigos.push_back((Inimigo*)new JJ(&jj,Vector2f(1980.f,-250.f),0.1f));//1
}

Fase1::~Fase1()
{
    //dtor
}

void Fase1::Executar(RenderWindow& window,float deltaTime, Jogador& jogador1,View& view,bool& _fimFase1){

    Sprite saloon(bar);
    saloon.setPosition(-260.f,-385.f);
    Sprite sprite(background);
    sprite.setPosition(-250.f,-1500.f);

    std::string aux ("vidas: ");
    std::stringstream aux2;
    aux2 << jogador1.getVida();
    aux += aux2.str();
    vidas.setString(aux);
    vidas.setFont(fonte);
    int antiga=jogador1.getVida();
    int caux=0;
    int caux2=0;

    if(jogador1.GetAtira()==true){
        if(jogador1.GetDireita()){
        bala.push_back(Projetil(&bala1,Vector2f(10.0f,4.f),Vector2f(jogador1.GetPosition().x+22.f,jogador1.GetPosition().y-19.f),jogador1));
        }
        else
         bala.push_back(Projetil(&bala22,Vector2f(10.0f,4.f),Vector2f(jogador1.GetPosition().x+22.f,jogador1.GetPosition().y-19.f),jogador1));
        gun.play();
        for(Projetil& tiro : bala){
        balaPos.push_back(tiro.GetPosition());
        }
    }

    for(Inimigo* inimigo1 : inimigos){
        if(inimigo1->GetAtira())
            bala2.push_back(ProjInimigo(&bala22,Vector2f(10.f,4.f),Vector2f(inimigo1->GetPosition().x-22.f,inimigo1->GetPosition().y-22.f)));
    }


    for(caux2=0; caux2<bala.size();caux2++){
        for(caux=0;caux<inimigos.size(); caux++){
            Collider(plat1)=inimigos[caux]->GetCollider();
            if(bala[caux2].GetCollider().CheckColisao(plat1,direction,1.f)){
                    bala.erase(bala.begin()+caux2);
                    balaPos.erase(balaPos.begin()+caux2);
                    if(inimigos[caux]->getVida()<=1){
                        inimigos.erase(inimigos.begin()+caux);
                    }
                    else{
                        inimigos[caux]->setVida(inimigos[caux]->getVida()-1);
                    }
            }
        }
  }

  for(caux2=0; caux2<bala.size();caux2++){
        for(caux=0;caux<balaPos.size(); caux++){
                if(abs(bala[caux2].GetPosition().x-balaPos[caux].x)>580.f){
                   balaPos.erase(balaPos.begin()+caux);
                   bala.erase(bala.begin()+caux2);
                }
        }
  }


  for(Plataforma& plataforma : plataformas){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador1.OnColisao(direction);
    }

    for(Plataforma& plataforma : invPlataforma){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador1.OnColisao(direction);
    }

    for(Obstaculo* obstaculo: obs){
        Collider(plat1)=jogador1.GetCollider();
        if(obstaculo->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.Move(-100.f,-100.f);
            jogador1.setVida((jogador1.getVida())-1);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }

    for(Inimigo* inimigo1: inimigos){
        Collider(plat1)=jogador1.GetCollider();
        if(inimigo1->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.Move(-100.f,-100.f);
            jogador1.setVida((jogador1.getVida())-1);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }

     for(caux=0; caux<bala2.size();caux++){
        Collider(plat1)=jogador1.GetCollider();
        bala2[caux].Atualiza();
        if(bala2[caux].GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            bala2.erase(bala2.begin() +caux);
            jogador1.Move(-100.f,0.f);
            jogador1.setVida((jogador1.getVida())-2);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }


     for(Plataforma plataforma: invChao){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.setVida((jogador1.getVida())-6);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }

    window.draw(sprite);
    window.draw(saloon);

    for(Plataforma& plataforma : plataformas)
        plataforma.Desenha(window);
    for(Obstaculo* obstaculo : obs)
        obstaculo->Desenha(window);
    for(Projetil tiro : bala)
        tiro.Desenha(window);
    for(Inimigo* inimigo : inimigos)
        inimigo->Desenha(window);
    for(ProjInimigo tiro : bala2)
        tiro.Desenha(window);


    if (jogador1.getVida()!=antiga)
    {
        aux2.str("");
        aux2 << jogador1.getVida();
        aux = ("vidas: ");
        aux += aux2.str();
        vidas.setString(aux);
        antiga=jogador1.getVida();
    }

    if(jogador1.GetPosition().x>5400.f){
        jogador1.setPosition(0.f,0.f);
        _fimFase1=true;
    }
    view.setCenter(jogador1.GetPosition().x+150.f,jogador1.GetPosition().y-(100.f));
    vidas.setPosition(jogador1.GetPosition().x-240, jogador1.GetPosition().y-400);

    window.setView(view);
    window.draw(vidas);

}

void Fase1::Executar2(RenderWindow& window,float deltaTime,Jogador& jogador1,View& view, Jogador2& jogador2,bool& _fimFase1){

    Sprite saloon(bar);
    saloon.setPosition(-260.f,-385.f);
    Sprite sprite(background);
    sprite.setPosition(-250.f,-1150.f);

    std::string aux21 ("vidas: ");
    std::stringstream aux22;
    aux22 << jogador2.getVida();
    aux21 += aux22.str();
    vidas2.setString(aux21);
    vidas2.setFont(fonte);
    int antiga2=jogador2.getVida();


    std::string aux ("vidas: ");
    std::stringstream aux2;
    aux2 << jogador1.getVida();
    aux += aux2.str();
    vidas.setString(aux);
    vidas.setFont(fonte);
    int antiga=jogador1.getVida();
    int caux=0;
    int caux2=0;


   if(jogador1.GetAtira()==true){
        if(jogador1.GetDireita()){
        bala.push_back(Projetil(&bala1,Vector2f(10.0f,4.f),Vector2f(jogador1.GetPosition().x+22.f,jogador1.GetPosition().y-19.f),jogador1));
        }
        else
         bala.push_back(Projetil(&bala22,Vector2f(10.0f,4.f),Vector2f(jogador1.GetPosition().x+22.f,jogador1.GetPosition().y-19.f),jogador1));
        gun.play();
        for(Projetil& tiro : bala){
        balaPos.push_back(tiro.GetPosition());
        }
    }

     if(jogador2.GetAtira()==true){
        if(jogador2.GetDireita()){
        bala2Jog.push_back(Projetil2(&bala1,Vector2f(10.0f,4.f),Vector2f(jogador2.GetPosition().x+22.f,jogador2.GetPosition().y-19.f),jogador2));
        }
        else
         bala2Jog.push_back(Projetil2(&bala22,Vector2f(10.0f,4.f),Vector2f(jogador2.GetPosition().x+22.f,jogador2.GetPosition().y-19.f),jogador2));
        gun.play();
        for(Projetil2& tiro : bala2Jog){
        balaPos2.push_back(tiro.GetPosition());
        }
    }

    for(Inimigo* inimigo1 : inimigos){
        if(inimigo1->GetAtira())
            bala2.push_back(ProjInimigo(&bala22,Vector2f(10.f,4.f),Vector2f(inimigo1->GetPosition().x-22.f,inimigo1->GetPosition().y-22.f)));
    }



    for(caux2=0; caux2<bala.size();caux2++){
        for(caux=0;caux<inimigos.size(); caux++){
            Collider(plat1)=inimigos[caux]->GetCollider();
            if(bala[caux2].GetCollider().CheckColisao(plat1,direction,1.f)){
                    bala.erase(bala.begin()+caux2);
                    balaPos.erase(balaPos.begin()+caux2);
                    if(inimigos[caux]->getVida()<=1){
                        inimigos.erase(inimigos.begin()+caux);
                    }
                    else{
                        inimigos[caux]->setVida(inimigos[caux]->getVida()-1);
                    }
            }
        }
  }


    for(caux2=0; caux2<bala2Jog.size();caux2++){
        for(caux=0;caux<inimigos.size(); caux++){
            Collider(plat1)=inimigos[caux]->GetCollider();
            if(bala2Jog[caux2].GetCollider().CheckColisao(plat1,direction,1.f)){
                    bala2Jog.erase(bala2Jog.begin()+caux2);
                    balaPos2.erase(balaPos2.begin()+caux2);
                    if(inimigos[caux]->getVida()<=1){
                        inimigos.erase(inimigos.begin()+caux);
                    }
                    else{
                        inimigos[caux]->setVida(inimigos[caux]->getVida()-1);
                    }
            }
        }
  }

  for(caux2=0; caux2<bala.size();caux2++){
        for(caux=0;caux<balaPos.size(); caux++){
                if(abs(bala[caux2].GetPosition().x-balaPos[caux].x)>580.f){
                   balaPos.erase(balaPos.begin()+caux);
                   bala.erase(bala.begin()+caux2);
                }
        }
  }

  for(caux2=0; caux2<bala2Jog.size();caux2++){
        for(caux=0;caux<balaPos2.size(); caux++){
                if(abs(bala2Jog[caux2].GetPosition().x-balaPos2[caux].x)>580.f){
                   balaPos2.erase(balaPos2.begin()+caux);
                   bala2Jog.erase(bala2Jog.begin()+caux2);
                }
        }
  }

  for(Plataforma& plataforma : plataformas){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador1.OnColisao(direction);
    }

     for(Plataforma& plataforma : plataformas){
        Collider(plat1)=jogador2.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador2.OnColisao(direction);
    }


    for(Plataforma& plataforma : invPlataforma){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador1.OnColisao(direction);
    }

     for(Plataforma& plataforma : invPlataforma){
        Collider(plat1)=jogador2.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f))
            jogador2.OnColisao(direction);
    }


    for(Obstaculo* obstaculo: obs){
        Collider(plat1)=jogador1.GetCollider();
        if(obstaculo->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.Move(-100.f,-100.f);
            jogador1.setVida((jogador1.getVida())-1);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }


    for(Obstaculo* obstaculo: obs){
        Collider(plat1)=jogador2.GetCollider();
        if(obstaculo->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador2.OnColisao(direction);
            jogador2.Move(-100.f,-100.f);
            jogador2.setVida((jogador2.getVida())-1);
            if(jogador2.getVida()<0)
            {
                jogador2.setPosition(0.f,-400.f);
                jogador2.setVida(5);
            }
        }
    }


    for(Inimigo* inimigo1: inimigos){
        Collider(plat1)=jogador1.GetCollider();
        if(inimigo1->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.Move(-100.f,-100.f);
            jogador1.setVida((jogador1.getVida())-1);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }

    for(Inimigo* inimigo1: inimigos){
        Collider(plat1)=jogador2.GetCollider();
        if(inimigo1->GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador2.OnColisao(direction);
            jogador2.Move(-100.f,-100.f);
            jogador2.setVida((jogador2.getVida())-1);
            if(jogador2.getVida()<0)
            {
                jogador2.setPosition(0.f,-400.f);
                jogador2.setVida(5);
            }
        }
    }


     for(caux=0; caux<bala2.size();caux++){
        Collider(plat1)=jogador1.GetCollider();
        if(bala2[caux].GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            bala2.erase(bala2.begin() +caux);
            jogador1.Move(-100.f,0.f);
            jogador1.setVida((jogador1.getVida())-2);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }

    for(caux=0; caux<bala2.size();caux++){
        Collider(plat1)=jogador2.GetCollider();
        if(bala2[caux].GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador2.OnColisao(direction);
            bala2.erase(bala2.begin() +caux);
            jogador2.Move(-100.f,0.f);
            jogador2.setVida((jogador2.getVida())-2);
            if(jogador2.getVida()<0)
            {
                jogador2.setPosition(0.f,-400.f);
                jogador2.setVida(5);
            }
        }
    }





     for(Plataforma plataforma: invChao){
        Collider(plat1)=jogador1.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador1.OnColisao(direction);
            jogador1.setVida((jogador1.getVida())-6);
            if(jogador1.getVida()<0)
            {
                jogador1.setPosition(0.f,-400.f);
                jogador1.setVida(5);
            }
        }
    }


     for(Plataforma plataforma: invChao){
        Collider(plat1)=jogador2.GetCollider();
        if(plataforma.GetCollider().CheckColisao(plat1,direction,1.f)){
            jogador2.OnColisao(direction);
            jogador2.setVida((jogador2.getVida())-6);
            if(jogador2.getVida()<0)
            {
                jogador2.setPosition(0.f,-400.f);
                jogador2.setVida(5);
            }
        }
    }

    if (jogador1.getVida()!=antiga)
    {
        aux2.str("");
        aux2 << jogador1.getVida();
        aux = ("vidas: ");
        aux += aux2.str();
        vidas.setString(aux);
        antiga=jogador1.getVida();
    }

    if (jogador2.getVida()!=antiga2)
    {
        aux22.str("");
        aux22 << jogador2.getVida();
        aux21 = ("");
        aux21 = aux22.str();
        vidas2.setString(aux21);
        antiga2=jogador2.getVida();
    }

    view.setCenter(jogador1.GetPosition().x+150.f,jogador1.GetPosition().y-(100.f));
    vidas.setPosition(jogador1.GetPosition().x-240, jogador1.GetPosition().y-400);

    window.draw(sprite);
    window.draw(saloon);

    for(Plataforma& plataforma : plataformas)
        plataforma.Desenha(window);
    for(Obstaculo* obstaculo : obs)
        obstaculo->Desenha(window);
    for(Projetil tiro : bala)
        tiro.Desenha(window);
    for(Projetil2 tiro2 : bala2Jog)
        tiro2.Desenha(window);
    for(Inimigo* inimigo : inimigos)
        inimigo->Desenha(window);
    for(ProjInimigo tiro : bala2)
        tiro.Desenha(window);


        if(jogador1.GetPosition().x>5400.f){
        jogador1.setPosition(0.f,0.f);
        jogador2.setPosition(0.f,0.f);
        _fimFase1=true;
        }

    vidas.setPosition(jogador1.GetPosition().x-240, jogador1.GetPosition().y-400);
    vidas2.setPosition(jogador1.GetPosition().x-140, jogador1.GetPosition().y-400);

    window.setView(view);
    window.draw(vidas);
    window.draw(vidas2);

}

void Fase1::Atualiza(float deltaTime){

    for(Projetil& tiro : bala)
        tiro.Atualiza();
    for(ProjInimigo& tiro : bala2)
        tiro.Atualiza();

    for(Inimigo* inimigo1 : inimigos)
        inimigo1->Atualiza(deltaTime);

    for(Obstaculo* obstaculo : obs)
        obstaculo->Atualiza(deltaTime);

}

void Fase1::Atualiza2(float deltaTime){

    for(Projetil& tiro : bala)
        tiro.Atualiza();
    for(ProjInimigo& tiro : bala2)
        tiro.Atualiza();

    for(Inimigo* inimigo1 : inimigos)
        inimigo1->Atualiza(deltaTime);

    for(Obstaculo* obstaculo : obs)
        obstaculo->Atualiza(deltaTime);

    for(Projetil2& tiro2 : bala2Jog)
        tiro2.Atualiza();

}
