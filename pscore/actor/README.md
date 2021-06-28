# Actor model design

It is easy to make the serving framework support data parallelism, but for model parallelism,
there are too many states to manage.

e.g. If we partition a large model into several services, there are some data communication between these services, 
considering there are some trivial optimization, for example, auto batching will make the logic more complex.

Further, if partition the while step network inside Transformer's decoder into several services, 
the loop should be supported, that is out of the traditional serving framework.

In such scenarios, data dataflow is complex, it is natural to abstract the system with an Actor model,
that is, each service is an Actor, and they executes the network and finally send messages(result tensors) to other Services.
For each Actor, there might be some optimizations when it receive an message, but all those details are the encapsulation details of that Actor.

All in all, by using the Actor model design, the complex model parallelism services can be decopuled and paratition into
multiple independent Actors, easy for testing and better performance.  


## Architecture

- ActorContext, the global context of all the actor, can create a actor.
- ActorRegistry, helps to register all the actors.
- Actor, a specific Actor class.

## Usages

### Create or lookup an actor

```c++
ActorContext ctx;

// get an actor with name of "ROOT/actor0"
auto* actor0 = ctx.Create<Actor>("actor0");

// get an actor with name of "ROOT/actor0/actor1"
auto* actor1 = actor0->ActorOf<Actor>("actor1");

// also get the actor1
auto* also_actor1 = ctx.LookupActor("ROOT/actor0/actor1");
```

### Define an actor

``` c++
class MyActor : public Actor {
public:
    explicit MyActor(absl::string_view name) : Actor(name) {}
    
    Status Receive(Message && message) override {
        // ...
    }
};
```
