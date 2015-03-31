/** ITCS-3146-002 Group 9 Project
 *  @name        Dining Philosophers
 *  @author      William Woodard
 *  @date        03/26/2015
 *  @description Uses asynchronous calls to simulate working threads and implement the dining philosophers problem in JavaScript
 */

'use strict';

//(function(){
  
  var API = (function(){
  
    function API() {
	  this.d = document;
    };
	
	API.prototype.select = function(selector, root) {
      return (root == null) ? document.body.querySelector(selector) : root.querySelector(selector);
	};
	
  	API.prototype.on = function(el, type, handler) {
      return (el.addEventListener) ? el.addEventListener(type, handler, false) : el.attachEvent("on" + type, handler);
    };
	
	API.prototype.rand = function(max, min) {
	  return min + (Math.random() * ((max - min) + 1));
	};
	
	API.prototype.modulo = function(n, m) {
      return ((n % m) + m) % m;
    };
	
	API.prototype.el = function(tag, properties) {
      var el;
	  
      el = document.createElement(tag);
      if (properties) {
        this.extend(el, properties);
      }
	  
      return el;
    };
	
	API.prototype.extend = function(object, properties) {
      var key,
	      val;
		  
      for (key in properties) {
        val = properties[key];
        object[key] = val;
      }
    };
	
	API.prototype.add = function(parent, child) {
      return parent.appendChild(child);
    };
	
	return API;
	
  })();
  
  var Philosopher = (function() {
    var id,
	    left,
		right,
		timesAte,
		stop,
		timeoutMax,
		timeoutMin;
    
	function Philosopher(no, left_fork, right_fork, pos) {
	  this.id = no;
	  this.left = left_fork;
	  this.right = right_fork;
	  this.timesAte = 0;
	  this.stop = false;
	  this.timeoutMin = 500;
	  this.timeoutMax = 2000;
	  
	  this.root = $.add($.select("#display"), $.el("span", {
	    className: "philosopher",
	    id: "philosopher_" + no,
		style: "left: " + pos.x + "px; top: " + pos.y + "px"
	  }));
	  this.image = $.add(this.root, $.el("img", {
	    className: "smiley",
	    src: "images/SmileyYellow.png"
	  }));
	  this.leftFork = $.add(this.root, $.el("img", {
	    className: "leftFork heldFork",
		src: "images/Fork.png"
	  }));
	  this.rightFork = $.add(this.root, $.el("img", {
	    className: "rightFork heldFork",
		src: "images/Fork.png"
	  }));
	  
	  this.leftFork.style.visibility = "hidden";
	  this.rightFork.style.visibility = "hidden";
	};
	
    Philosopher.prototype.setPos = function(pos) {
	  this.root.style.left = pos.x + "px";
	  this.root.style.top = pos.y + "px";
	};
	
	Philosopher.prototype.dine = function() {
	  if (this.stop !== true) {
	    this.think();
	  } else {
	    GUI.log("Philosopher " + this.id + " stops. (Ate " + this.timesAte + " times)");
	  }
	};
	
	Philosopher.prototype.done = function() {
	  this.stop = true;
	};
	
	Philosopher.prototype.think = function() {
	  var ref = this;
	  GUI.log("Philosopher " + this.id + " thinks...");
	  this.image.src = "images/SmileyYellow.png";
	  window.setTimeout(function() {
	    if (ref.left.get(ref.id) == true) {
		  ref.showLeft();
		  if (ref.right.get(ref.id) == true) { 
		    ref.showRight();
		    ref.eat();
		  } else {
		    ref.left.put(ref.id);
			ref.right.put(ref.id);
			ref.hideLeft();
			ref.hideRight();
			ref.wait();
		  }
		} else {
		  ref.left.put(ref.id);
		  ref.right.put(ref.id);
	      ref.hideLeft();
	      ref.hideRight();
		  ref.wait();
		}
	  }, $.rand(this.timeoutMax, this.timeoutMin));
	};
	
	Philosopher.prototype.eat = function() {
	  var ref = this;
	  this.timesAte++;
	  GUI.log("Philosopher " + this.id + " eats. Yum! (" + this.timesAte + " time(s))");
	  this.image.src = "images/SmileyGreen.png";
	  window.setTimeout(function() {
	    ref.left.put(ref.id);
		ref.right.put(ref.id);
	    ref.hideLeft();
		ref.hideRight();
		ref.dine();
	  }, $.rand(this.timeoutMax, this.timeoutMin));
	};
	
	Philosopher.prototype.wait = function() {
	  var ref = this;
	  GUI.log("Philosopher " + this.id + " waits...");
	  this.image.src = "images/SmileyRed.png";
	  window.setTimeout(function() {
	    ref.dine();
	  }, $.rand(this.timeoutMax / 2, this.timeoutMin));
	};
	
	Philosopher.prototype.showLeft = function() {
	  this.leftFork.style.visibility = "visible";
	};
	
	Philosopher.prototype.showRight = function() {
	  this.rightFork.style.visibility = "visible";
	};
	
	Philosopher.prototype.hideLeft = function() {
	  this.leftFork.style.visibility = "hidden";
	};
	
	Philosopher.prototype.hideRight = function() {
	  this.rightFork.style.visibility = "hidden";
	};
	
	return Philosopher;
	
  })();
  
  var Fork = (function() {
    var id,
	    inUse;
		
	function Fork(no, pos, angle) {
	  this.id = no;
	  this.inUse = false;
	  this.state = new Semaphore(1);
	  this.inUseBy = false;
	  
	  this.root = $.add($.select("#display"), $.el("span", {
	    className: "fork",
	    id: "fork_" + no,
		style: "left: " + pos.x + "px; top: " + pos.y + "px; transform: rotate(" + (angle + Math.PI) + "rad)"
	  }));
	  this.image = $.add(this.root, $.el("img", {
	    className: "forky",
	    src: "images/Fork.png"
	  }));
	};
	
	Fork.prototype.setPos = function(pos, angle) {
	  this.root.style.left = pos.x + "px";
	  this.root.style.top = pos.y + "px";
	  this.root.style.transform = "rotate(" + (angle + Math.PI) + "rad)";
	};
	
	Fork.prototype.get = function(philosopher) {
      var does, trial;
	  if (this.inUse == false) {
	    does = " picks up ";
		this.inUse = true;
		this.inUseBy = philosopher;
		trial = true;
		this.image.src = "images/Blank.png";
	  } else {
	    does = " missed ";
		trial = false;
	  }
	  
	  GUI.log("Philosopher " + philosopher + does + "fork " + this.id);
	  
	  return trial;
	};
	
	Fork.prototype.put = function(philosopher) {
	  if (this.inUseBy == philosopher) {
	    GUI.log("Philosopher " + philosopher + " puts down fork " + this.id);
	    this.inUse = false;
		this.inUseBy = false;
		this.image.src = "images/Fork.png";
	  }
	};
	
	return Fork;
	
  })();
  
  var Semaphore = (function() {
    var state,
	    count;
	
	function Semaphore(no) {
	  this.set(no);
	  return this.state;
	}
	
	Semaphore.prototype.set = function(no) {
	  this.count = no;
	  this.state = this.test();
	};
	
	Semaphore.prototype.test = function() {
	  return (count > 0) ? true : false;
	};
	
	Semaphore.prototype.decrement = function() {
	  this.count--;
	  this.state = this.test();
	};
	
	Semaphore.prototype.increment = function() {
	  this.count++;
	  this.state = this.test();
	};
	
	return Semaphore;
	
  })();
  
  var GUI_Template = (function() {
    var root,
	    console,
		controls;
    
    function GUI_Template() {
	  this.root = $.select("#gui");
	  this.console = $.select("#console", this.root);
	  this.controls = $.select("#controls", this.root);
	  
	  $.on($.select("#btnStart", this.controls), "click", Main.start);
	  $.on($.select("#btnStop", this.controls), "click", Main.stop);
	  $.on($.select("#btnClear", this.controls), "click", this.clear);
	  $.on($.select("#btnSet", this.controls), "click", this.setPhilosophers);
	}
	
	GUI_Template.prototype.log = function(str) {
	  this.console.innerHTML += str + "<br />";
	  this.console.scrollTop = this.console.scrollHeight;
	};
	
	GUI_Template.prototype.clear = function() {
	  GUI.console.innerHTML = "<strong>Console</strong><br />";
	};
	
	GUI_Template.prototype.setPhilosophers = function() {
	  var num = $.select("[name=\"numPhilosophers\"]").value;
	  Main.init(parseInt(num));
	};
	
	GUI_Template.prototype.disableSet = function() {
	  $.select("#btnSet", this.controls).disabled = true;
	};
	
	GUI_Template.prototype.enableSet = function() {
	  $.select("#btnSet", this.controls).disabled = false;
	};
	
	return GUI_Template;
	
  })();
  
  var Main = {
    running: false,
    init: function(num) {
	  var d = document,
          db = document.body,
          h = document.head,
		  forks = {},
		  philosophers = {},
		  numberOfPhilosophers = (typeof num == "number") ? num : 5,
          numberOfForks = numberOfPhilosophers,
	      pos = {},
	      container_width = $.select("#display").clientWidth - 256,
		  container_height = $.select("#display").clientHeight - 256,
		  radius = 160,
		  radius_fork = 96,
		  angle = 0,
		  angle_fork = 0,
		  step = (2 * Math.PI) / numberOfPhilosophers;
		  
	  $.select("#display").innerHTML = '<img id="table" src="images/Table.png" />';
      window.GUI = new GUI_Template();
	  
      for (var i = 0; i < numberOfForks; i++) {
        pos.x = (container_width + 256 - 64) / 2 + radius_fork * Math.cos(angle_fork + 1 / 4 * Math.PI);
        pos.y = (container_height + 256 - 64) / 2 + radius_fork * Math.sin(angle_fork + 1 / 4 * Math.PI);
        angle_fork += step;
	    forks[i] = new Fork(i, pos, angle_fork);
	  }
	  
	  for (var i = 0; i < numberOfPhilosophers; i++) {
        pos.x = container_width / 2 + radius * Math.cos(angle);
        pos.y = container_height / 2 + radius * Math.sin(angle);
        angle += step;
	    philosophers[i] = new Philosopher(i, forks[$.modulo(i - 1, numberOfForks)], forks[$.modulo(i, numberOfForks)], pos);
	  }
	
	  console.log(philosophers);
	  console.log(forks);
	  window.philosophers = philosophers;
	  window.forks = forks;
	  window.numberOfPhilosophers = numberOfPhilosophers;
	  GUI.enableSet();
	  setInterval(Main.position, 1000);
    },
	stop : function() {
      var philosophers = window.philosophers,
	      forks = window.forks,
	  	  numberOfPhilosophers = window.numberOfPhilosophers;

      if (Main.running === true) {
	    for (var i = 0; i < numberOfPhilosophers; i++) {
	      philosophers[i].done();
	    }
		
		Main.running = false;
		GUI.enableSet();
	  }
    },
    start : function() {
	  var numberOfPhilosopher = window.numberOfPhilosophers,
	      philosophers = window.philosophers;
      
	  if (Main.running === false) {
	    for (var i = 0; i < numberOfPhilosophers; i++) {
		  philosophers[i].stop = false;
	      philosophers[i].dine();
	    }
	    
	    Main.running = true;
		GUI.disableSet();
	  }
    },
	position : function() {
	  var forks = window.forks,
		  philosophers = window.philosophers,
		  numberOfPhilosophers = window.numberOfPhilosophers,
          numberOfForks = numberOfPhilosophers,
	      pos = {},
	      container_width = $.select("#display").clientWidth - 256,
		  container_height = $.select("#display").clientHeight - 256,
		  radius = 160,
		  radius_fork = 96,
		  angle = 0,
		  angle_fork = 0,
		  step = (2 * Math.PI) / numberOfPhilosophers;
	  
      for (var i = 0; i < numberOfForks; i++) {
        pos.x = (container_width + 256 - 64) / 2 + radius_fork * Math.cos(angle_fork + 1 / 4 * Math.PI);
        pos.y = (container_height + 256 - 64) / 2 + radius_fork * Math.sin(angle_fork + 1 / 4 * Math.PI);
        angle_fork += step;
	    forks[i].setPos(pos, angle_fork);
	  }
	  
	  for (var i = 0; i < numberOfPhilosophers; i++) {
        pos.x = container_width / 2 + radius * Math.cos(angle);
        pos.y = container_height / 2 + radius * Math.sin(angle);
        angle += step;
	    philosophers[i].setPos(pos);
	  }
	}
  };
  
  var $ = new API();
  $.on(document, 'DOMContentLoaded', function() {
    Main.init(5);
  });
  
//}).call(this);