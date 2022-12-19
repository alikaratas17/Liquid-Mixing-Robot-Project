import 'package:flutter/material.dart';
import 'package:mixture_selector/drink_widget.dart';

import 'order_drink.dart';
class MyApplication extends StatelessWidget{

  Widget build(BuildContext context){
    return MaterialApp(title:"Mixture Selector", home:MyHomePage());
  }
}

class MyHomePage extends StatelessWidget{
  @override
  Widget build(BuildContext context) { 
    return Scaffold(appBar: AppBar(title: Text('Mixture Selection')),
    body: 
          ElevatedButton(onPressed: (){
            Navigator.of(context).push(MaterialPageRoute(builder: (context) => MyOrderScreen()));
          }
          , child: const Text('Make Mixture'))
           //,)
    );
  }

}