import 'package:flutter/material.dart';
import 'my_key.dart' as my_key;
import 'package:http/http.dart' as http;
import 'drink_widget.dart';


class MyOrderScreen extends StatefulWidget{
  @override
  State<StatefulWidget> createState() {
    return MyOrderScreenState();
  }
}
class MyOrderScreenState extends State<MyOrderScreen>{
  var drinks = ["Lemon Juice", "Orange Juice", "Grenadine Juice", "Apple Juice"];
  //var amounts = [0.0,0.0,0.0,0.0];
  late List<MyDrinkWidget> drink_widgets;

  MyOrderScreenState(){
    this.drink_widgets = drinks.map((x){return MyDrinkWidget(x);}).toList();
  }
  @override
  Widget build(BuildContext context){
    //return //MaterialApp(title:"Select a Mixture",home:
    return Scaffold(appBar: AppBar(title: Text('Mixture Selection')),
    body: Column(children:
          [Column(children: this.drink_widgets,),
          ElevatedButton(onPressed: send_mixture, child: Text('Make Mixture'))]
           ,)
    );//);
    /*
    return MaterialApp(title: 'Select a Mixture',
    home:Scaffold(appBar: AppBar(title: Text('Mixture Selection')),body: Column(children: [
      Column(children:[Text(drinks[0]+" : "+amounts[0].toString()),ElevatedButton(onPressed: increase0, child: Text('Increase')),]),
      Column(children:[Text(drinks[1]+" : "+amounts[1].toString()),ElevatedButton(onPressed: increase1, child: Text('Increase')),]),
      Column(children:[Text(drinks[2]+" : "+amounts[2].toString()),ElevatedButton(onPressed: increase2, child: Text('Increase')),]),
      Column(children:[Text(drinks[3]+" : "+amounts[3].toString()),ElevatedButton(onPressed: increase3, child: Text('Increase')),]),
      Text('Please Select one of below'),
      ElevatedButton(onPressed: send_mixture, child: Text('Make Mixture')),
    ]),));
    */
  }
  /*
void increase0(){
  setState(() {
    amounts[0]+=0.5;
  });
}
void increase1(){
  setState(() {
    amounts[1]+=0.5;
  });
}
void increase2(){
  setState(() {
    amounts[2]+=0.5;
  });
}
void increase3(){
  setState(() {
    amounts[3]+=0.5;
  });
}*/
void send_mixture() async{

  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  var amounts = [0,0,0,0];
  amounts[0] +=this.drink_widgets[0].my_state.amount;
  amounts[1] +=this.drink_widgets[1].my_state.amount;
  amounts[2] +=this.drink_widgets[2].my_state.amount;
  amounts[3] +=this.drink_widgets[3].my_state.amount;

  this.drink_widgets[0].my_state.reset();
  this.drink_widgets[1].my_state.reset();
  this.drink_widgets[2].my_state.reset();
  this.drink_widgets[3].my_state.reset();
  /*
  double total = amounts.reduce((v, e) => v+e)+1e-12; // Check if this is valid to get sum
  var percentages = [0,0,0,0];
  for (int i = 0; i< 3; i++)
    percentages[i] = (100.0*amounts[i]/total).round();
  percentages[3] = 100 - percentages.reduce((v, e) => v+e); // Check if this is valid to get sum
  String mixture = percentages[0].toString()+','+percentages[1].toString()+','+percentages[2].toString()+','+percentages[3].toString(); // Format should be 4 ints (percentages) separated by ','
  */
  String mixture = amounts[0].toString()+','+amounts[1].toString()+','+amounts[2].toString()+','+amounts[3].toString(); // Format should be 4 ints (amounts) separated by ','
  final response = await http.post(Uri.parse(my_url),body:{'value':mixture});
  print(response.statusCode.toString()); // For debugging
}
}
/*
void opt1_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 1";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt2_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 2";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt3_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 3";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}
void opt4_func() async{
  String my_url = 'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key='+ my_key.key;
  String option = "Option 4";
  final response = await http.post(Uri.parse(my_url),body:{'value':option});
  print(response.statusCode.toString());
}*/