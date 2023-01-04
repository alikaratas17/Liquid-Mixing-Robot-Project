import 'dart:ffi';

import 'package:flutter/material.dart';
import 'my_key.dart' as my_key;
import 'package:http/http.dart' as http;
import 'drink_widget.dart';

class MyOrderScreen extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return MyOrderScreenState();
  }
}

class MyOrderScreenState extends State<MyOrderScreen> {
  bool _ischecked = false;
  double _max_amount = 200.0;
  var drinks = [
    "Lemon Juice",
    "Orange Juice",
    "Grenadine Juice",
    "Apple Juice"
  ];
  //var amounts = [0.0,0.0,0.0,0.0];
  late List<MyDrinkWidget> drink_widgets;
  String message = "";

  MyOrderScreenState() {
    this.drink_widgets = drinks.map((x) {
      return MyDrinkWidget(x, _ischecked);
    }).toList();
  }
  @override
  Widget build(BuildContext context) {
    Color getColor(Set<MaterialState> states) {
      const Set<MaterialState> interactiveStates = <MaterialState>{
        MaterialState.pressed,
        MaterialState.hovered,
        MaterialState.focused,
      };
      if (states.any(interactiveStates.contains)) {
        return Colors.blue;
      }
      return Colors.red;
    }

    //return //MaterialApp(title:"Select a Mixture",home:
    return Scaffold(
        appBar: AppBar(title: Text('Custom Mixture Selection')),
        body: Container(
          alignment: Alignment.center,
          child: Column(
            children: [
              Text(message),
              Column(
                children: this.drink_widgets,
              ),
              Container(
                  child: Row(
                    children: [
                      Text("Percentage"),
                      Checkbox(
                        checkColor: Colors.white,
                        fillColor: MaterialStateProperty.resolveWith(getColor),
                        value: _ischecked,
                        onChanged: (bool? value) {
                          setState(() {
                            _ischecked = value!;
                            for (int i = 0; i < 4; i++)
                              this
                                  .drink_widgets[i]
                                  .my_state
                                  .changeText(_ischecked);
                          });
                        },
                      )
                    ],
                  ),
                  alignment: Alignment.center),
              ElevatedButton(
                  onPressed: send_mixture, child: Text('Make Mixture'))
            ],
          ),
        ));
  }

  void send_mixture() async {
    String my_url =
        'https://io.adafruit.com/api/v2/akaratas17/feeds/message/data?X-AIO-Key=' +
            my_key.key;
    var amounts = [0.0, 0.0, 0.0, 0.0];
    if(_ischecked){
    var percentages = [0.0, 0.0, 0.0, 0.0];
    percentages[0] += this.drink_widgets[0].my_state.amount;
    percentages[1] += this.drink_widgets[1].my_state.amount;
    percentages[2] += this.drink_widgets[2].my_state.amount;
    percentages[3] += this.drink_widgets[3].my_state.amount;
    var total_percentage =percentages[0]+percentages[1]+percentages[2]+percentages[3];
    if (total_percentage==0.0)return;
    amounts[0] = (10*_max_amount * percentages[0]/total_percentage).round()*1.0/10;
    amounts[1] = (10*_max_amount * percentages[1]/total_percentage).round()*1.0/10;
    amounts[2] = (10*_max_amount * percentages[2]/total_percentage).round()*1.0/10;
    amounts[3] = _max_amount -amounts[0]-amounts[1]-amounts[2];
    }else{
    amounts[0] += this.drink_widgets[0].my_state.amount;
    amounts[1] += this.drink_widgets[1].my_state.amount;
    amounts[2] += this.drink_widgets[2].my_state.amount;
    amounts[3] += this.drink_widgets[3].my_state.amount;
    var total_amount =amounts[0]+amounts[1]+amounts[2]+amounts[3];
    if (total_amount==0.0 || total_amount > _max_amount)return;
      
    }
    String tmp_message = "Order Received\n";
    for (int i = 0; i < 4; i++) {
      if (this.drink_widgets[i].my_state.amount > 0)
        tmp_message = tmp_message +
            this.drink_widgets[i].my_state.name +
            " : " +
            amounts[i].toString() +
            " mL \n";
    }
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
    String mixture = amounts[0].toString() +
        ',' +
        amounts[1].toString() +
        ',' +
        amounts[2].toString() +
        ',' +
        amounts[3]
            .toString(); // Format should be 4 ints (amounts) separated by ','
    final response =
        await http.post(Uri.parse(my_url), body: {'value': mixture});
    print(response.statusCode.toString()); // For debugging

    setState(() {
      message = tmp_message;
    });
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
