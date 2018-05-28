open Fetcher;

type spot = data;

type state =
  | Inactive
  | Loading
  | Idle(array(spot));

type action =
  | DataFetch
  | DataFetched(array(spot));

let component = ReasonReact.reducerComponent("Main");

/* underscores before names indicate unused variables. We name them for clarity */
let make = _children => {
  ...component,
  initialState: () => Inactive,
  reducer: (action, _state) =>
    switch (action) {
    | DataFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            fetchGet(
              ~url="https://immense-river-25513.herokuapp.com/locations",
              ~cb=data =>
              self.send(DataFetched(data))
            )
        ),
      )
    | DataFetched(spots) => ReasonReact.Update(Idle(spots))
    },
  didMount: self => self.send(DataFetch),
  render: self =>
    <ComposableMap
      projectionConfig={scale: 800, rotation: [0, 0, 0]}
      width=980
      height=551>
      <ZoomableGroup center=(0, 0) disablePanning=true>
        <Geographies geography="./world-50m.json">
          ...(
               (geographies, projection) =>
                 geographies
                 |> Belt.Array.mapWithIndex(_, (i, geography) =>
                      <Geography
                        key=(string_of_int(i))
                        geography
                        projection
                      />
                    )
             )
        </Geographies>
        (
          switch (self.state) {
          | Inactive
          | Loading => <div />
          | Idle(spots) =>
            <Markers>
              (
                spots
                |> Belt.Array.mapWithIndex(
                     _,
                     (i, spot: spot) => {
                       let (lat, long) = Fetcher.location(spot);
                       <Marker
                         key=(string_of_int(i))
                         marker=(
                           Marker.markerT(
                             ~markerOffset=-25,
                             ~name=Fetcher.username(spot),
                             ~coordinates=[|long, lat|],
                           )
                         )>
                         <circle
                           cx="0"
                           cy="0"
                           r="10"
                           style=(
                             ReactDOMRe.Style.make(
                               ~stroke="#FF5722",
                               ~strokeWidth="3",
                               ~opacity="0.9",
                               (),
                             )
                           )
                         />
                       </Marker>;
                     },
                   )
              )
            </Markers>
          }
        )
      </ZoomableGroup>
    </ComposableMap>,
};