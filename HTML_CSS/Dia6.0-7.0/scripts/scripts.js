var nome = document.getElementById("txt_nome")
var tmp = document.getElementById("txt_tmp")
var cat = document.getElementById("txt_cat")
var carddestino = document.getElementById("destino")

function add() {
  var clone = document.getElementById("origem").cloneNode(true);
  var destino = document.getElementById("destino");
  destino.appendChild(clone);

  var camposClonados = clone.getElementsByTagId("txt_nome");

  for (i = 0; i < camposClonados.length; i++) {
    camposClonados[i].value = "";
  }

  carddestino.innerHTML = `
            <h2>${nome.value}</h2>
            <br><br><br>
            <h2>${tmp.value} min</h2>
            <h2>${cat.value}</h2><br>
  `;

  nome.value = '';
  tmp.value = '';
  cat.value = '';
}

function remove(id) {
  var node1 = document.getElementById("destino");
  node1.removeChild(node1.childNodes[0]);
}
