<!doctype html>
<?php
session_start();
if(isset($_SESSION['tipo']))
	header('location:index.php');
?>
<html class="no-js">

	<head>
		<meta charset="utf-8"/>
		<title>FOLDER TEMPLATE</title>
		
		<!--[if lt IE 9]>
			<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
		<![endif]-->
		<link rel="stylesheet" media="all" href="css/style.css"/>
		<meta name="viewport" content="width=device-width, initial-scale=1"/>
		<!-- Adding "maximum-scale=1" fixes the Mobile Safari auto-zoom bug: http://filamentgroup.com/examples/iosScaleBug/ -->		
				
		<!-- JS -->
		<script src="js/jquery-1.7.1.min.js"></script>
		<script src="js/custom.js"></script>
		<script src="js/tabs.js"></script>
		<script src="js/css3-mediaqueries.js"></script>
		<script src="js/jquery.columnizer.min.js"></script>
		
		<!-- Isotope -->
		<script src="js/jquery.isotope.min.js"></script>
		
		<!-- Lof slider -->
		<script src="js/jquery.easing.js"></script>
		<script src="js/lof-slider.js"></script>
		<link rel="stylesheet" href="css/lof-slider.css" media="all"  /> 
		<!-- ENDS slider -->
		
		<!-- Tweet -->
		<link rel="stylesheet" href="css/jquery.tweet.css" media="all"  /> 
		<script src="js/tweet/jquery.tweet.js" ></script> 
		<!-- ENDS Tweet -->
		
		<!-- superfish -->
		<link rel="stylesheet" media="screen" href="css/superfish.css" /> 
		<script  src="js/superfish-1.4.8/js/hoverIntent.js"></script>
		<script  src="js/superfish-1.4.8/js/superfish.js"></script>
		<script  src="js/superfish-1.4.8/js/supersubs.js"></script>
		<!-- ENDS superfish -->
		
		<!-- prettyPhoto -->
		<script  src="js/prettyPhoto/js/jquery.prettyPhoto.js"></script>
		<link rel="stylesheet" href="js/prettyPhoto/css/prettyPhoto.css"  media="screen" />
		<!-- ENDS prettyPhoto -->
		
		<!-- poshytip -->
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-twitter/tip-twitter.css"  />
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-yellowsimple/tip-yellowsimple.css"  />
		<script  src="js/poshytip-1.1/src/jquery.poshytip.min.js"></script>
		<!-- ENDS poshytip -->
		
		<!-- JCarousel -->
		<script type="text/javascript" src="js/jquery.jcarousel.min.js"></script>
		<link rel="stylesheet" media="screen" href="css/carousel.css" /> 
		<!-- ENDS JCarousel -->
		
		<!-- GOOGLE FONTS -->
		<link href='http://fonts.googleapis.com/css?family=Voltaire' rel='stylesheet' type='text/css'>

		<!-- modernizr -->
		<script src="js/modernizr.js"></script>
		
		<!-- SKIN -->
		<link rel="stylesheet" media="all" href="css/skin.css"/>
		
		<!-- Less framework -->
		<link rel="stylesheet" media="all" href="css/lessframework.css"/>
		
		<!-- jplayer -->
		<link href="player-skin/jplayer-black-and-yellow.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" src="js/jquery.jplayer.min.js"></script>
		
		<!-- flexslider -->
		<link rel="stylesheet" href="css/flexslider.css" >
		<script src="js/jquery.flexslider.js"></script>
		
		<!-- reply move form -->
		<script src="js/moveform.js"></script>
		
		<!-- star -->
		<link rel="stylesheet" media="all" href="css/star.css"/>
		
	</head>
	
	<?php
		if(isset($newCliente)){
			if($newCliente){
				echo"<script type='text/javascript'>";
				echo "alert('Cliente cadastrado com sucesso!');";
				echo "</script>";
			}
			else{
				echo"<script type='text/javascript'>";
				echo "alert('Não foi possível realizar o cadastro!');";
				echo "</script>";
			}
		}
	?>
	
	<body class="page" onload="">
	
		<!-- HEADER -->
		<header>
			<div class="wrapper cf">
				
				<div id="logo">
					<a href="index.php"><img  src="img/logo.png" alt="Simpler"></a>
				</div>
				
				<!-- nav -->
					<ul id="nav" class="sf-menu">
	<li "><a href="index.php">HOME</a></li>
<?php
if(!(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja')) {
	echo '<li><a href="products.php">PRODUTOS</a></li>';
	echo '<li><a href="#">LOJAS</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'cliente') {
	echo '<li><a href="history.php">HISTÓRICO</a></li>';
	echo '<li><a href="car.php">CARRINHO</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja') {
	echo '<li><a href="#">HISTORICO</a></li>';
	echo '<li><a href="registerProducts.php">CADASTRAR PRODUTO</a></li>';
	echo '<li><a href="#">GERENCIAR PROMOÇÃO</a></li>';
}
?>

					
					<li><a href="contact.php">CONTATO</a></li>
<?php
	if(!(isset($_SESSION['tipo']))) {
				echo<<< HTML
					<li class="current-menu-item"><a href="#">LOGIN</a>
						<ul>
							<li>
								<script type="text/javascript" src="js/form-validation.js"></script>
								<table>
									<tr>
										<td>
											<form action="validate.php" method="POST">
											<fieldset style="width:100px" size="100">
												Usuário 							
												<input name="user"  id="user" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="password"  id="password" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerCliente.php">Cadastrar cliente </a>
											</fieldset>
											</form>
											</script>
										</td>
										<td>								
											<script type="text/javascript" src="js/form-validation.js"></script>
											<form action="validate.php" method="POST">
											<fieldset>
												CNPJ 							
												<input name="CNPJ"  id="CNPJ" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="senha"  id="senha" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerLoja.php">Cadastrar loja </a>
											</fieldset>
											</form>
											</script>
										</td>
									</tr>
								</table>
							</li>
						</ul>
						
					</li>
HTML;
	} else {
		echo '<li><a href="logout.php">SAIR</a></li>';
	}
?>
				</ul>
				<div id="combo-holder"></div>
				<!-- ends nav -->

			</div>
		</header>
		<!-- ENDS HEADER -->
		
		<!-- MAIN -->
		<div id="main">
			<div class="wrapper cf">
			
			
				
			<!-- page content-->
        	<div id="page-content" class="cf">        	
	        		
	        	
	 
				<!-- page content-->
				
				<p><h3>CADASTRAR CLIENTE</h3></p>
				<!-- form -->
				<script type="text/javascript" src="js/form-validation.js"></script>
				<form id="contactForm" action="insertCliente.php" method="post">
					<fieldset>
														
						<p>
							<label for="name" >Nome</label>
							<input name="name"  id="name" type="text" class="form-poshytip" title="Digite seu nome" />
						</p>
						
						<p>
							<label for="name2" >Sobrenome</label>
							<input name="name2"  id="name2" type="text" class="form-poshytip" title="Digite seu sobrenome" />
						</p>
					
						<p>
							<label for="usuario" >Usuario</label>
							<input name="usuario"  id="usuario" type="text" class="form-poshytip" title="Digite seu usuario" />
						</p>
						
						<p>
							<label for="password" >SENHA</label>
							<input name="password"  id="password" type="text" class="form-poshytip" title="Digite sua senha" />
						</p>
						
						<p>
							<label for="email" >E-Mail</label>
							<input name="email"  id="email" type="text" class="form-poshytip" title="Digite seu email" />
						</p>
						
						<p>
							<label for="tel" >Telefone</label>
							<input name="tel"  id="tel" type="text" class="form-poshytip" title="Digite seu telefone" />
						</p>
					
						<p>
							<label for="CPF" >CPF</label>
							<input name="CPF"  id="CPF" type="text" class="form-poshytip" title="Digite seu CPF" />
						</p>
						
						<p>
							<label for="estado" >ESTADO - UF</label>
							<input name="estado"  id="estado" type="text" class="form-poshytip" title="Digite seu estado. EX: MG" />
						</p>
						
						
						<p><input type="submit" value="Enviar" name="submit" id="submit" /> <span id="error" class="warning">Mensagem</span></p>
					</fieldset>
					
				</form>
				
				<!-- ENDS form -->				
				
    		</div>
    		<!-- ENDS page content-->
			
			
			
			</div><!-- ENDS WRAPPER -->
		</div>
		<!-- ENDS MAIN -->
		
		
		<!-- FOOTER -->
		<footer>
			<div class="wrapper cf">
			
				<!-- widgets -->
				<ul  class="widget-cols cf">
					<li class="first-col">
						
						<div class="widget-block">
							<h4>RECENT POSTS</h4>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
						</div>
					</li>
					
					<li class="second-col">
						
						<div class="widget-block">
							<h4>ABOUT</h4>
							<p>Folder it's completely free this means you don't have to pay anything <a href="http://luiszuno.com/blog/license" tar >read license</a>.</p> 
							<p>Visit <a href="http://templatecreme.com/" >Template Creme</a> and find the most beautiful free templates up to date.</p>
						</div>
						
					</li>
					
					<li class="third-col">
						
						<div class="widget-block">
							<div id="tweets" class="footer-col tweet">
		         				<h4>TWITTER WIDGET</h4>
		         			</div>
		         		</div>
		         		
					</li>
					
					<li class="fourth-col">
						
						<div class="widget-block">
							<h4>CATEGORIES</h4>
							<ul>
								<li class="cat-item"><a href="#" >Design</a></li>
								<li class="cat-item"><a href="#" >Photo</a></li>
								<li class="cat-item"><a href="#" >Art</a></li>
								<li class="cat-item"><a href="#" >Game</a></li>
								<li class="cat-item"><a href="#" >Film</a></li>
								<li class="cat-item"><a href="#" >TV</a></li>
							</ul>
						</div>
		         		
					</li>	
				</ul>
				<!-- ENDS widgets -->	
				
				
				<!-- bottom -->
				<div class="footer-bottom">
						<ul id="social-bar" class="cf sb">
							<li><a href="http://www.facebook.com"  title="Become a fan" class="facebook">Facebbok</a></li>
							<li><a href="http://www.twitter.com" title="Follow my tweets" class="twitter"></a></li>
							<li><a href="http://plus.google.com" title="Enter my circles" class="plus"></a></li>
						</ul>
				</div>	
				<!-- ENDS bottom -->
			
			</div>
		</footer>
		<!-- ENDS FOOTER -->
		
		<!-- Start google map -->
		<script>initialize();</script>
	
	</body>
	
	
	
</html>