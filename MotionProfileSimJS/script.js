
class TrapezoidalMotionProfile {
    constructor( maxVel,  maxAcc,distance) {

    this.m_distanceTotal = distance;
    this.m_maxVel = maxVel;
    this.m_maxAcc = maxAcc;
    
  this.m_accelTime = this.m_maxVel / this.m_maxAcc;

  this.m_decelTime = this.m_maxVel / this.m_maxAcc;

  this.m_distanceAccel = .5 * this.m_accelTime * this.m_maxVel;

  this.m_distanceDecel = .5 * this.m_decelTime * this.maxVel;

  this.m_distanceCoast = this.m_distanceTotal - (2 * this.m_distanceAccel);

  this.m_coastTime = this.m_distanceCoast / this.m_maxVel;
  
  if (this.m_distanceCoast < 0) {
    this.m_accelTime = Math.sqrt(this.m_distanceTotal / this.m_maxAcc);

		this.m_decelTime = Math.sqrt(this.m_distanceTotal / this.m_maxAcc);

    this.m_distanceCoast = 0;

    this.m_distanceAccel = this.m_distanceTotal / 2;
    this.m_distanceDecel = this.m_distanceTotal / 2;
		this.m_coastTime = 0;
  }



  this.m_totalTime = this.m_accelTime + this.m_coastTime + this.m_decelTime;

}
    calculatempVelocity(t) {
    if(t < this.m_accelTime) {
        return(t * this.m_maxAcc);
    }

    else if(t > this.m_accelTime && t < (this.m_accelTime + this.m_coastTime)) {
        return(this.m_maxVel);
    }

    else if(t > this.m_accelTime + this.m_coastTime && t < this.m_totalTime) {
        return((this.m_totalTime - t) * this.m_maxAcc);
    }

    return 0;
    }

    calculatempAcceleration(t) {
        if(t < this.m_accelTime) {
            return(this.m_maxAcc);
        }
    
        else if(t > this.m_accelTime && t < (this.m_accelTime + this.m_coastTime)) {
            return(0);
        }
    
        else if(t > this.m_accelTime + this.m_coastTime && t < this.m_totalTime) {
            return(-1 * this.m_maxAcc);
        }
    
        return 0;
        }
    

}

// var userMaxVel = window.prompt("Enter your max Vel: ");
// var userMaxAcc = window.prompt("Enter your max Acc: ");
// var userDistance = window.prompt("Enter your distance: ");


var startButton = document.getElementById("start");

var poseCanvas = document.getElementById("drawPose");

var inputMaxVel;
var inputMaxAcc;
var inputDistance
function setInputs() {

inputMaxVel = document.getElementById("maxVel").valueAsNumber;
inputMaxAcc = document.getElementById("maxAcc").valueAsNumber;
inputDistance = document.getElementById("distance").valueAsNumber;

if(isNaN(inputMaxVel) ) {
    alert("please enter max Vel value")
    location.reload();}
else if(isNaN(inputMaxAcc) ) {
    alert("please enter max Acceleration value")
    location.reload();
}
else if(isNaN(inputDistance)  ) {
    alert("please enter distance value")
    location.reload();
}
else if(isNaN(inputMaxVel) && isNaN(inputMaxAcc)) {
    alert("please enter max velocity and acceleration values")
    location.reload();
}
else if(isNaN(inputMaxVel) && isNaN(inputDistance)) {
    alert("please enter max velocity and distance values")
    location.reload();
}
else if(isNaN(inputMaxAcc) && isNaN(inputDistance)) {
    alert("please enter max acceleration and distance values")
    location.reload();
}
else if(isNaN(inputMaxAcc) && isNaN(inputDistance)&& isNaN(inputMaxVel)) {
    alert("please enter max Velocity, max acceleration and distance values")
    location.reload();
}

}

startButton.onclick = function() {
  setInputs();
var prevData = []
function initTrap() {
trap = new TrapezoidalMotionProfile(inputMaxVel,inputMaxAcc,inputDistance);

}

initTrap();

     var time =0;
     var velArray = [];
     var accArray = [];
     var poseArray = [];
     var pose = 0;
    while(time<trap.m_totalTime) {
        var linearVel = trap.calculatempVelocity(time);
        velArray.push(trap.calculatempVelocity(time));
        accArray.push(trap.calculatempAcceleration(time));
        poseArray.push(pose);
        time+= .01;
        pose += .01* linearVel;
    }

    for(i =0; i< velArray.length; i++) {
        console.log(poseArray[i]);
    }


function pushPoseData() {
    var POSEDATA =[];
   var timee = 0;
   for(i =0; i< poseArray.length; i ++) {
       POSEDATA.push(
           {x: timee,
           y: poseArray[i] }
           );
      timee +=.01
  
    }
  return(POSEDATA);
    }

    function pushVelData() {
var VELDATA =[];
  var timee = 0;
  for(i =0; i< velArray.length; i ++) {
      VELDATA.push(
          {x: timee,
          y: velArray[i] }
          );
     timee +=.01
 
 }
 return(VELDATA);
}

function pushAccData() {
var ACCDATA =[];
 var timee = 0;
 for(i =0; i< accArray.length; i ++) {
     ACCDATA.push(
         {x: timee,
         y: accArray[i] }
         );
    timee +=.01

}
return(ACCDATA);
}

  var ctx = document.getElementById("myPoseChart").getContext("2d");
  
  startButton.poseChart = new Chart(ctx, {
  type: 'scatter',
  data: {
     datasets: [{
        label: "Position",
        data: pushPoseData(),
     }]
  },
  options: {
      responsive: true,
  }
});
var ctx = document.getElementById("myPoseChart").getContext("2d");
  
startButton.poseChart = new Chart(ctx, {
type: 'scatter',
data: {
   datasets: [{
      label: "Position",
      data: pushPoseData(),
   }]
},
options: {
    responsive: true,
}
});
var ctx = document.getElementById("myVelChart").getContext("2d");
  
startButton.velChart = new Chart(ctx, {
type: 'scatter',
data: {
   datasets: [{
      label: "Velocity",
      data: pushVelData(),
   }]
},
options: {
    responsive: true,
}
});
var ctx = document.getElementById("myAccChart").getContext("2d");
  
startButton.accChart = new Chart(ctx, {
type: 'scatter',
data: {
   datasets: [{
      label: "Acceleration",
      data: pushAccData(),
   }]
},
options: {
    responsive: true,
}
});
console.log(inputMaxVel);
}

//  startButton.addEventListener("click", function(e){
//    e.preventDefault();

// });

//  var velChart = new Chart(document.getElementById("myVelChart"), {
//     type: 'scatter',
//     data: {
//        datasets: [{
//           label: "Velocity",
//           data: pushVelData(),
//        }]
//     },
//     options: {
//         responsive: true,
//     }
//  });

//  var accChart = new Chart(document.getElementById("myAccChart"), {
//     type: 'scatter',
//     data: {
//        datasets: [{
//           label: "Acceleration",
//           data: pushAccData(),
//        }]
//     },
//     options: {
//         responsive: true,
//     }
//  });

 


/*
let myChart = document.getElementById('myChart').getContext('2d');
    
        // Global Options
        Chart.defaults.global.defaultFontFamily = 'Lato';
        Chart.defaults.global.defaultFontSize = 18;
        Chart.defaults.global.defaultFontColor = '#777';
    
        let massPopChart = new Chart(myChart, {
          type:'line', // bar, horizontalBar, pie, line, doughnut, radar, polarArea
          data:{
            datasets:[{
              label:'Population',
              data:velArray,
              //backgroundColor:'green',
              backgroundColor:[
                'rgba(255, 99, 132, 0.6)',
                'rgba(54, 162, 235, 0.6)',
                'rgba(255, 206, 86, 0.6)',
                'rgba(75, 192, 192, 0.6)',
                'rgba(153, 102, 255, 0.6)',
                'rgba(255, 159, 64, 0.6)',
                'rgba(255, 99, 132, 0.6)'
              ],
              borderWidth:1,
              borderColor:'#777',
              hoverBorderWidth:3,
              hoverBorderColor:'#000'
            }]
          },
          options:{
            title:{
              display:true,
              text:'Largest Cities In Massachusetts',
              fontSize:25
            },
            legend:{
              display:true,
              position:'right',
              labels:{
                fontColor:'#000'
              }
            },
            layout:{
              padding:{
                left:50,
                right:0,
                bottom:0,
                top:0
              }
            },
            tooltips:{
              enabled:true
            }
          }
        });


*/

        