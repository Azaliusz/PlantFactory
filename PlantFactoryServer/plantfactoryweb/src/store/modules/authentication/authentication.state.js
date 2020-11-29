const initializeState = function() {
  return {
    user: null
  };
};

export default {
  user: initializeState().user,
  initializeState: initializeState
};
