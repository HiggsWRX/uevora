<%@page import="java.util.Vector"%>
<%@page language="java" contentType="text/html"%>
<%@page import="eshop.beans.Espaco"%>

<%-- Isto é um comentário JSP... --%>
<%-- a indicacao abaixo disponibiliza a variável dataManager, para acesso aos dados --%>
<jsp:useBean id="dataManager" scope="application" class="eshop.model.DataManager"/>

<%
    String base = (String) application.getAttribute("base");
    String imageURL = (String) application.getAttribute("imageURL");
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <title>Espacos Disponiveis</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <h2>Consultar disponibilidade de um espaço</h2>
            <p>Espaco a consultar</p>
            <form style="border: 0px solid; padding: 0; margin: 0;">
                <input type="hidden" name="action" value="availform"/>
                <input type="radio" name="space" value="FUT01" required/>Futsal
                <input type="radio" name="space" value="TEN01" required/>Tenis
                <input type="radio" name="space" value="PAD01" required/>Padel<br>
                <p>Dia a reservar</p>
                <input type="date" name="date" required/><br>
                <p>Hora</p>
                <input type="time" name="time" required/><br>
                <input id="submit" type="submit" value="Submit"/>
            </form>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
