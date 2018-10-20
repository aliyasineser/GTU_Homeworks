//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package hwconnection;

simple Router
{
    parameters:
    	@display("p=250,250,ri,200,200");
    gates:
        input routerIn[];
        output routerOut[];
        input nodeIn[];
        output nodeOut[];
        input swin;
        output swout;
}


simple Node
{

    gates:
        input in;
        output out;
}


simple Server
{
    parameters:
    	@display("p=350,445,ri,100,100");
    gates:
        input in[];
        output out[];
}



//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network TopConnection
{
    parameters:
    	int n = default(3);
    	int m = default(9);
	types:
        channel Channel extends ned.DelayChannel {
            delay = 250ms;
        }
    submodules:
        routerArr[n]: Router;
		nodeArr[m]: Node;
		server: Server;
    connections:
        
        for i=0..n-1 {
        	routerArr[i].routerOut++ --> Channel --> routerArr[(i+1)%n].routerIn++;
        	routerArr[i].routerIn++ <-- Channel <-- routerArr[(i+1)%n].routerOut++;
        	
        	routerArr[i].swout --> Channel --> server.in++;
        	routerArr[i].swin <-- Channel <-- server.out++;
        	
        }
       

        for i=0..m-1 {
        	nodeArr[i].out --> Channel --> routerArr[i%n].nodeIn++;
        	nodeArr[i].in <-- Channel <-- routerArr[i%n].nodeOut++;
        }
}

