<!DOCTYPE html>
<html>
<head>
<meta http-equiv="refresh" content="20">
<link href="//netdna.bootstrapcdn.com/bootstrap/3.1.0/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
<script src="//netdna.bootstrapcdn.com/bootstrap/3.1.0/js/bootstrap.min.js"></script>
<script src="//code.jquery.com/jquery-1.11.1.min.js"></script>
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
<style>
* {
  box-sizing: border-box;
  
}

#myInput {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 5%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
 
}
#myInput2 {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 10%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
}
#myInput3 {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 10%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
}
#myInput4 {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 10%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
}
#myInput5 {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 10%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
}
#myInput6 {
  background-image: url('/css/searchicon.png');
  background-position: 10px 10px;
  background-repeat: no-repeat;
  width: 10%;
  font-size: 16px;
  padding: 2px 2px 2px 4px;
  border: 1px solid #ddd;
  margin-bottom: 12px;
}

#myTable {
  border-collapse: collapse;
  width: 100%;
  border: 1px solid #ddd;
  font-size: 18px;
}

#myTable th, #myTable td {
  text-align: left;
  padding: 12px;
}

#myTable tr {
  border-bottom: 1px solid #ddd;
}

#myTable tr.header, #myTable tr:hover {
  background-color: #f1f1f1;
}
</style>
</head>
<body>

<?php

$servername = "localhost";
$dbname = "iotbasedwq";
$username = "root";
$password = "";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT ID, sensor1, temperature, sensor2, pH, sensor3, TDS, decision, datetime FROM iotdb ORDER BY ID DESC";
?>
<div>
<h3>Search by</h3>
<h4 style="padding-left:100px;" >ID
<input type="text" id="myInput" onkeyup="myFunction()" placeholder="ID" title="Type in a ID">
Temperature
<input type="text" id="myInput2" onkeyup="myFunction2()" placeholder="Temperature" title="Type in a Temperature">
pH
<input type="text" id="myInput3" onkeyup="myFunction3()" placeholder="pH" title="Type in a pH">
TDS
<input type="text" id="myInput4" onkeyup="myFunction4()" placeholder="TDS" title="Type in a TDS">
Type of Water
<input type="text" id="myInput5" onkeyup="myFunction5()" placeholder="Water Type" title="Type in a Water Type">
Date & Time
<input type="text" id="myInput6" onkeyup="myFunction6()" placeholder="Date & Time" title="Type in a Date & Time">
</div>
<div class="container">
    
    <div class="row">
        <div class="panel panel-primary filterable">
            <div class="panel-heading">
                <h3 class="panel-title" align="center">IoT Based Water Quality Monitoring System</h3>
              
            </div>
            <table id="myTable">
                
                    <tr class="header">
                        <th>ID</th>
                        <th>Temperature</th>
						<th>Type of Temperature</th>
                        <th>pH</th>
						<th>Type of pH</th>
                        <th>TDS</th>
						<th>Type of TDS</th>
						<th>Type of Water</th>
						<th>Date & Time</th>
                    </tr>   
<?php
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_ID = $row["ID"];
        $row_sensor1 = $row["sensor1"];
		$row_temperature = $row["temperature"];
        $row_sensor2 = $row["sensor2"];
		$row_pH = $row["pH"];
        $row_sensor3 = $row["sensor3"];
		$row_TDS = $row["TDS"];
        $row_decision = $row["decision"]; 
        $row_datetime = $row["datetime"];
		?>
      
             <tr> 
                <td><?php echo $row_ID ?></td> 
                <td><?php echo $row_sensor1 ?></td> 
				<td><?php echo $row_temperature ?></td> 
                <td><?php echo $row_sensor2 ?></td>
				<td><?php echo $row_pH ?></td>				
                <td><?php echo $row_sensor3 ?></td> 
                <td><?php echo $row_TDS ?></td>
				<td><?php echo $row_decision ?></td>
                <td><?php echo $row_datetime ?></td>  
              </tr>
			  <?php
    }
    $result->free();
}

$conn->close();
?> 
               
            </table>
        </div>
    </div>
</div>


<script>
function myFunction() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[0];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
function myFunction2() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput2");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[1];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
function myFunction3() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput3");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[3];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
function myFunction4() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput4");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[5];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
function myFunction5() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput5");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[7];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
function myFunction6() {
  var input, filter, table, tr, td, i, txtValue;
  input = document.getElementById("myInput6");
  filter = input.value.toUpperCase();
  table = document.getElementById("myTable");
  tr = table.getElementsByTagName("tr");
  for (i = 0; i < tr.length; i++) {
    td = tr[i].getElementsByTagName("td")[8];
    if (td) {
      txtValue = td.textContent || td.innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        tr[i].style.display = "";
      } else {
        tr[i].style.display = "none";
      }
    }       
  }
}
</script>

</body>
</html>