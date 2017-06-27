<%@page import="eshop.beans.Reserva"%>
<%@page import="java.util.Vector"%>
<%@page language="java" contentType="text/html"%>
<%@page import="eshop.beans.Espaco"%>

<%-- Isto � um coment�rio JSP... --%>
<%-- a indicacao abaixo disponibiliza a vari�vel dataManager, para acesso aos dados --%>
<jsp:useBean id="dataManager" scope="application" class="eshop.model.DataManager"/>

<%
    String base = (String) application.getAttribute("base");
    String imageURL = (String) application.getAttribute("imageURL");
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <title>Consultar disponibilidade de um espa�o</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <%
                String codEsp = request.getParameter("space");
                String date = request.getParameter("date");
                String time = request.getParameter("time");
                String datetime = date + " " + time;

                if (dataManager.verifySpace(codEsp, datetime)) {
            %><p>Espa�o disponivel!</p><%
                } else {
            %> <p>Espa�o indisponivel. Tente outra data.</p> <%
                }
            %>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
