#!/usr/bin/python
# -*- coding: utf-8 -*-
from string import translate

english_words = set([
"the","of","and","to","a","in","for","is","on","that","by","this","with","i","you","it","not","or","be","are",
"from","at","as","your","all","have","new","more","an","was","we","will","home","can","us","about","if","page",
"my","has","search","free","but","our","one","other","do","no","information","time","they","site","he","up",
"may","what","which","their","news","out","use","any","there","see","only","so","his","when","contact","here",
"business","who","web","also","now","help","get","pm","view","online","c","e","first","am","been","would",
"how","were","me","s","services","some","these","click","its","like","service","x","than","find"
]); 

french_words = set([
"de","la","le","et","les","des","en","un","du","une","que","est","pour","qui","dans","a","par","plus","pas",
"au","sur","ne","se","le","ce","il","sont","la","les","ou","avec","son","il","aux","d'un","en","cette","d'une",
"ont","ses","mais","comme","on","tout","nous","sa","mais","fait",u'été',"aussi","leur","bien","peut","ces","y",
"deux","a","ans","l","encore","n'est","marché","d","pour","donc","cours","qu'il","moins","sans","c'est","et",
"si","entre","un","ce","faire","elle","c'est","peu","vous","une","prix","on","dont","lui","également","dans",
"effet","pays","cas","ee","millions","belgique","bef","mois","leurs","taux","années","temps","groupe"
]);

german_words = set([
"der","und","die","in","ist","von","den","des","eine","im","ein","mit","das","zu","für","dem","sich","auf",
"als","auch","wird","oder","aus","wurde","werden","sind","an","einer","nicht","durch","nach","bei","es",
"war","zum","er","zur","am","einem","einen","sie","bis","man","über","um","dass","wie","hat","eines","nur",
"stadt","kann","bezeichnet","noch","aber","siehe","vor","so","unter","gemeinde","vom","isbn","wurden","sie",
"zwischen","gibt","of","jahre","dieser","sein","diese","können","haben","literatur","m","zeit","mehr",
"geschichte","liegt","zwei","name","seine","jedoch","sehr","deutschland","sowie","seiner","seit","jahr",
"dann","heute","â","de","anderen","begriff","etwa","waren","wenn","gegen","jahren"
]);

spanish_words = set([
"que","de","no","a","la","el","es","y","en","lo","un","por","qué","me","una","te","los","se","con","para",
"mi","está","si","bien","pero","yo","eso","las","sí","su","tu","aquí","del","al","como","le","más",
"esto","ya","todo","esta","vamos","muy","hay","ahora","algo","estoy","tengo","nos","tú","nada","cuando",
"ha","este","sé","estás","así","puedo","cómo","quiero","sólo","soy","tiene","gracias","o","él","bueno",
"fue","ser","hacer","son","todos","era","eres","vez","tienes","creo","ella","he","ese","voy","puede",
"sabes","hola","sus","porque","dios","quién","nunca","dónde","quieres","casa","favor","esa","dos","tan",
"señor","tiempo","verdad","estaba"
]);

def detect(words):
	model = [ ("English", english_words), ("French", french_words),
						("German", german_words), ("Spanish", spanish_words) ]
	m = max(model, key=lambda x : len(set(words).intersection(x[1])))
	return m[0]

if __name__ == "__main__":
	text = translate(raw_input(), None, ".,!?:\";").lower().split()
	print detect(text)
	
