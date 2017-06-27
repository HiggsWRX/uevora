<%@page import="eshop.beans.Reserva"%>
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
        <title>Consultar disponibilidade de um espaço</title>
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
            %><p>Espaço disponivel!</p><%
                } else {
            %> <p>Espaço indisponivel. Tente outra data.</p> <%
                }
            %>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
