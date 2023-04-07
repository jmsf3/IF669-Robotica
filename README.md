# IF669-Robotica
Projeto extra da cadeira de Introdução à Programação do CIn-UFPE utilizando o simulador de robôs [CoppeliaSim](https://www.coppeliarobotics.com/).

# Objetivo
O projeto consiste em desenvolver um progama na linguagem __C++__ que seja capaz de ler um arquivo de texto, que contém um número arbitrário de votos, e simular uma votação na urna eletrônica com o braço robótico __Niryo One__.

# Funcionamento
* __Conexão com o simulador__
* __Leitura do arquivo de texto__
* __Movimentação do braço através de cinemática inversa__

# Conexão
Para realizar a conexão com o simulador usamos uma [API remota](https://www.coppeliarobotics.com/helpFiles/en/legacyRemoteApiOverview.htm) que já está disponível dentro do próprio CoppeliaSim.

# Leitura
Através dos headers __<stdio.h>__ e __<stdlib.h>__ lemos o arquivo __"votos.txt"__ e armazenamos os votos lidos em um __vetor dinâmico__ de strings.

# Movimentação
* A movimentação do braço se deu por meio da manipulação dos ângulos das juntas do robô. A configuração final das juntas foi obtida da seguinte maneira através de cinemática inversa:

* Ângulo da base ($\beta$)
<p align="center">
  <img src="cinematica-inversa-1.png" />
</p>

$$
\Large 
\tag{1.1}
tg(\beta) = \frac{x_t - x_b}{y_t - y_b} \implies \beta = arctg(\frac{x_t - x_b}{y_t - y_b})
$$

* Ângulos das articulções ($\alpha_1$ e $\alpha_2$)
<p align="center">
  <img src="cinematica-inversa-2.png" />
</p>

$$
\tag{1.2}
\Large tg(\phi) = \frac{z_t - z_b}{\sqrt{(x_t - x_b)^2 + (y_t - y_b})^2} \implies \phi = arctg(\frac{z_t - z_b}{\sqrt{(x_t - x_b)^2 + (y_t - y_b})^2})
$$

$$
\tag{1.3}
\Large (l_2)^2 = d^2 + (l_1)^2 - 2dl_1cos(\theta) \implies \theta = arccos(\frac{d^2 + (l_1)^2 - (l_2)^2}{2dl_1})
$$

$$
\tag{1.4}
\Large (l_1)^2 = d^2 + (l_2)^2 - 2dl_2cos(\gamma) \implies \gamma = arccos(\frac{d^2 + (l_2)^2 - (l_1)^2}{2dl_2})
$$

$$
\tag{1.5}
\Large \alpha_1 + \theta + \phi = \frac{\pi}{2} \implies \alpha_1 = \frac{\pi}{2} - (\theta + \phi)
$$

$$
\tag{1.6}
\Large (\frac{\pi}{2} + \alpha_2) + \theta + \gamma = \pi \implies \alpha_2 = \frac{\pi}{2} - (\theta + \gamma)
$$

# Imagens
<p align="center">
  <img src="braco-inicial.png" />
</p>

<p align="center">
  <img src="braco-tecla.png" />
</p>

<p align="center">
  <img src="braco-confirma.png" />
</p>
