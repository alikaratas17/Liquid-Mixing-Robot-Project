import 'package:flutter/material.dart';



class MyDrinkWidget extends StatefulWidget{
  late MyDrinkWidgetState my_state;
  MyDrinkWidget(name,is_checked){
    this.my_state =  MyDrinkWidgetState(name,is_checked);
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
  var is_checked;
  var text_to_write;
  double amount = 0.0;
  double max_amount = 50.0;
  MyDrinkWidgetState(name,is_checked){
    this.name = name;
    this.is_checked = is_checked;
    this.text_to_write =   name+" : "+amount.toString()+ " ml";
    if (is_checked)
      this.text_to_write =   name+" : "+amount.toString()+ " part";
  }
  @override
  Widget build(BuildContext context){
    return Column(children:[Text(text_to_write,textAlign: TextAlign.center,),
    //Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,children: [
    //ElevatedButton(onPressed: increase, child: Text('Increase')),
    //ElevatedButton(onPressed: decrease, child: Text('Decrease')),
    Slider(
      value: amount,
      max:max_amount,
      divisions:(max_amount/5).round(),
      label:amount.toString(),
      onChanged:(double value){
        if (value <= max_amount){
        setState((){
          amount = value;
  text_to_write = getNewText();
        });
        }
      })
    //])
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
void changeText(is_checked){
    this.is_checked = is_checked;
    setState(() {
  text_to_write = getNewText();
    });
}
String getNewText(){
    var part_or_ml=" ml";
    if(this.is_checked){
      part_or_ml = " part";
    }
  return name+" : "+amount.toString()+part_or_ml;
}
}