import 'package:flutter/material.dart';
import 'my_key.dart' as my_key;
import 'package:http/http.dart' as http;



class MyDrinkWidget extends StatefulWidget{
  late MyDrinkWidgetState my_state;
  MyDrinkWidget(name){
    this.my_state =  MyDrinkWidgetState(name);
  }

  @override
  State<StatefulWidget> createState() {
    return my_state;
  }
}
class MyDrinkWidgetState extends State<MyDrinkWidget>{
  //var drinks = ["Lemon Juice", "Orange Juice", "Grenadine Juice", "Apple Juice"];
  //var amounts = [0.0,0.0,0.0,0.0];
  var name;
  var amount = 0;
  MyDrinkWidgetState(this.name);
  @override
  Widget build(BuildContext context){
    return Column(children:[Text(name+" : "+amount.toString(),textAlign: TextAlign.center,),
    Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,children: [
    ElevatedButton(onPressed: increase, child: Text('Increase')),
    ElevatedButton(onPressed: decrease, child: Text('Decrease')),
    ])
    ]
    );
  }
void increase(){
  setState(() {
  amount ++;
  });
}
void decrease(){
  if (amount <= 0)return;
  setState(() {
  amount --;
  });
}
void reset(){
  setState((){
    amount = 0;
  });
}
}