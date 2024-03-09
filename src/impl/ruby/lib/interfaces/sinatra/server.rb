require 'sinatra/base'

require_relative 'stored_game'

Dir.chdir File.dirname(__FILE__)

module GameOfLife
  module Interfaces
    module Sinatra
      class Server < ::Sinatra::Base
        get '/' do
          File.read File.join('public', 'index.html')
        end

        get '/world' do
          StoredGame.response
        end

        post '/world/tick' do
          StoredGame.tick!
          StoredGame.response
        end
      end
    end
  end
end
